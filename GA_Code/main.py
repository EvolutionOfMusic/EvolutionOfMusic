from SongPersistance import load_songs as load_pheno_list, save_songs
from BiasedRandomSequence import BiasedRandomSequence, sample_pair
from ConfigFile import ConfigFile
from RandomSongGen import random_song, tempo_gen as meta_gen, random_chromosome
from GeneticRandomizer import GeneticRandomizer
from SongPersistance import load_songs, save_songs
from GeneticSong import min_nc_length
from DiversityCalc import get_avg_diversity

from random import SystemRandom, seed, randrange
from argparse import ArgumentParser
from math import sqrt
import sys
from os import system, path
import logging

CONFIG_FILE_PATH = "GA_Code/pyth_main.config"
LOG_FILE_PATH = "main_log.txt"

random_track_id = lambda song, randomizer: randomizer.sample(song.track_ids, 1)[0]

"""
This program can be called the following ways

python3 main.py -n (for a new genome with no seed)
python3 main.py -n -s <seed number> (for new genome with seed)
python3 main.oy -g (to run after a genome has been graded)

The -p option specifies the pid of a process responsible for
calling this code, and is None by default
"""

def get_crossover_prob(i, pc=60):
    """
    Inputs: i (the index of a pheno_type in a list, where said list is ordered by fitness)
            pc (the probability that the most fit phenotype will crossover)
    Outputs: a probability (from 0 to 100), which depends primarily on i
    """
    pc /= 100
    prob = (pc*(1 - pc)**i)*100
    return int(prob)

def init_arg_parser():
    """
    Inputs: None
    Outputs: an arg parser, capable of parseing the --new (-n), --seed, (-s)
    """
    parser = ArgumentParser()
    parser.add_argument('-n', "--new", help="creates new genome", action="store_true")
    parser.add_argument('-s', "--seed", help="specifies seed for new genome", type=int)
    parser.add_argument('-p', "--pid", help="pid for calling code", type=int) 
    return parser.parse_args() 

def alert_parent_program(pid):
    """
    Inputs: pid (the pid of the program that called this code)
    Outputs: a SIGCONT signal to the process with the matching pid
    """
    if pid is not None:
        system("kill -CONT " + str(pid))

def write_to_output_file(output_file_name, *phenos):
    """
    Inputs: output_file_name, which the *phenos will be written in string from
    for purposes other than data persistance
    Outputs: to a file in raw text format
    """
    with open(output_file_name, 'w+') as save:
        save.write(str(len(penos)) + '\n')
        for pheno in phenos:
            save.write(str(pheno) + '\n') 

def get_gen_num(pheno, config_file):
    """
    Inputs: pheno, config_file
    Outputs: the number of generations that came before a pheno, add 1
    """
    return pheno.song_id//config_file.song_count

def get_population_sample(config_obj, *phenos):
    gen_num = get_gen_num(phenos[0], config_obj)
    wv = []
    for pheno in phenos:
        if wv == []:
            wv.append(pheno)
        elif wv[len(wv) - 1].score == pheno.score:
            continue
        else:
            wv.append(pheno) 
        
        if len(wv) == config_obj.sample_size:
            break 
        
    write_to_output_file(config_obj.sample_file + "_generation_{}"
                         .format(gen_num), *wv)

def get_avg(*scores):
    """
    computes the average score
    """
    return round(sum([score for score in scores])/len(scores)) 

def append_to_graph_file(file_name, gen_num, *value):
    """
    Inputs: file_name (name of the graph file), the generation number, the values to be plotted
    Outputs: a graph file with the list of values appended to it
    """
    with open(file_name, 'a') as graph:
        graph.write(str(gen_num))
        for i in value:
            graph.write(" " + str(i)) 
        graph.write('\n');

def clear_file(file_name):
    """
    Removes everything written in the specified file
    """
    with open(file_name, 'w') as graph:
        graph.write(str(''))

def read_input_file_line(file_obj):
    """
    Input: a file object
    Output: a line from the file, the file object represents
    as a tupel of integers 
    """
    return tuple(map(int, file_obj.readline().split()))

def get_pheno_list(config_file):
    """
    Input: config_file (a config file object)
    Output: a list of phenotypes

    This function is normally used during initialiation.
    """
    return [random_song(config_file) for i in range(config_file.song_count)]

def save_pheno_list_to_file(pheno_list, config_file):
    """
    Inputs: pheno_list (a list of pheno_types), config_file (a config file object)
    Outputs: a file containing the phenotypes in pheno_list

    This function is primarily for data persistance
    """
    save_songs(config_file.save_file, *pheno_list)
    write_to_output_file(config_file.save_file, *pheno_list)
    alert_parent_program(args.pid)

def log_cross_over(pheno1, pheno2, c_over_point):
    """
    Inputs: pheno1 and pheno2 (the two phenotypes being crossed over)
            c_over_point (the point where the two pheno types will crossover)
    Output: a record of the crossover

    """
    logging.info("phenotypes {} and {} with fitnesses {} {}, crossed over, at {}"
                         .format(pheno1.song_id, pheno2.song_id, pheno1.score, pheno2.score, c_over_point))
    
def delete_mutation(pheno3, randomizer):
    """
    Inputs: pheno3 (a pheno type), randomizer (a randomizer specializing in genetic operations)
    Outputs: a pheno type, with a portion missing 
    """
    del_track_id = randomizer.sample_one_item(pheno3.track_ids) 
    pheno3.chromosome_delete(del_track_id)
    return pheno3

def add_mutation(pheno3, config_file):
    """
    Inputs: pheno3 (a pheno type), config_file (a config file object)
    Outputs: a phenotype with a portion added to it 
    """
    pheno3.chromosome_add(random_chromosome(config_file)) 
    return pheno3
    
def mutation(pheno3, config_file):
    """
    Inputs: pheno3 (a phenotype), config_file (a config_file object)
    Outputs: a phenotype with portions of it changed
    """
    meta_data = meta_gen(config_file) 
    delta_mask = randomizer.get_delta_mask(config_file.max_step_size, pheno3, meta_data)
    pheno3.mutate(*delta_mask)
    return pheno3

def log_delete_mutation(pheno3):
    logging.info("phenotype {}, was mutated (chromo delete)".format(pheno3.song_id))

def log_add_mutation(pheno3): 
    logging.info("phenotype {}, was mutated (chromo add)".format(pheno3.song_id))

def log_mutation(pheno3):
    logging.info("phenotype {}, was mutated".format(pheno3.song_id))

def find_min_pheno(pheno_list, config_file):
    """
    Inputs: pheno_list (list of pheno_types), config_file (config_file object)
    Outputs: the pheno_type with the lowest score

    This function is usually used to ensure that the  with the lowest score
    is passed on to the next generation 
    """
    top_pheno = min(pheno_list, key=lambda v: v.score)
    top_pheno.song_id = (gen_num + 1) * config_file.song_count
    return top_pheno

def find_max_pheno(pheno_list, config_file):
    """
    Inputs: pheno_list (list of pheno_types), config_file (config_file object)
    Outputs: the phenotype with the highest score
    """
    top_pheno = max(pheno_list, key=lambda v: v.score)
    top_pheno.song_id = (gen_num + 1) * config_file.song_count
    return top_pheno

def get_pheno_count(config_file):
    """
    Inputs: config_file (a config file object)
    Output: the number of phenotypes in a generation
    """
    return config_file.song_count
    
if __name__ == "__main__":
    #initialization
    args = init_arg_parser()
    
    randomizer = GeneticRandomizer(SystemRandom())
    
    logging.basicConfig(filename=LOG_FILE_PATH, level=logging.DEBUG)
    
    if path.exists(CONFIG_FILE_PATH) and path.isfile(CONFIG_FILE_PATH):
       config_file = ConfigFile(CONFIG_FILE_PATH)
    else:
        raise OSError("config file: {}, not found".format(CONFIG_FILE_PATH))

    if args.new:
        #first time setup
        clear_file(LOG_FILE_PATH)
        clear_file(config_file.graph_file)
        seed(args.seed)
        pheno_list = get_pheno_list(config_file)

        #saving and exiting
        save_pheno_list_to_file(pheno_list, config_file)
        raise SystemExit  
    else:
        # post grading setup
        pheno_list = load_pheno_list(config_file.save_file, config_file)
        score_list = []
        diversity_list = []
        with open(config_file.input_file) as save:
            for pheno in pheno_list:
                score, diversity = read_input_file_line(save)
                score_list.append(score)
                diversity_list.append(abs(diversity))
                pheno.score = score * config_file.score_scale_factor
                pheno.diversity = diversity * config_file.div_scale_factor + 1
            pheno_list.sort(key=lambda v: v.score//v.diversity, reverse=False)
            for i in range(len(pheno_list)):
                pheno_list[i].crossover_chance = get_crossover_prob(i)
            clear_file(config_file.input_file)
    
    #calcuation and outputing of vital statistics
    get_population_sample(config_file, *pheno_list)
    logging.info("avg fitness: {}, max fitness: {}, min fitness: {}".format(get_avg(*score_list), max(score_list), min(score_list)))
    gen_num = get_gen_num(pheno_list[1], config_file)
    value_list = [get_avg(*score_list), max(score_list), min(score_list), get_avg(*diversity_list)]
    append_to_graph_file(config_file.graph_file, gen_num, *value_list)

    #pre-crossover setup
    new_pheno_list = []
    top_pheno = find_min_pheno(pheno_list, config_file)
    new_pheno_list.append(top_pheno)
    pheno_list = BiasedRandomSequence(*pheno_list, insert_key=lambda v: v.crossover_chance) 
    
    #crossover/mutation loop
    for i in range(get_pheno_count(config_file) - 1):
        #phenotype selection
        pheno1, pheno2 = sample_pair(pheno_list)
        c_over_point = randomizer.get_crossover_point(pheno1, pheno2)
        pheno3 = pheno1.crossover(pheno2, c_over_point)
        log_cross_over(pheno1, pheno2, c_over_point)

        #mutation phase
        if randomizer.get_prob() <= config_file.mutation_chance:
            if randomizer.get_prob() <= config_file.chromo_delete_prob and len(pheno3) > 1:
                pheno3 = delete_mutation(pheno3, randomizer)
                log_delete_mutation(pheno3)
            elif randomizer.get_prob() <= config_file.chromo_add_prob:
                pheno3 = add_mutation(pheno3, config_file)
                log_add_mutation(pheno3)
            else:
                pheno3 = mutation(pheno3, config_file)
                log_mutation(pheno3)
                
        new_pheno_list.append(pheno3)

    #saving and exiting
    pheno_list = new_pheno_list
    save_pheno_list_to_file(pheno_list, config_file)
    raise SystemExit
