from SongPersistance import load_songs, save_songs
from BiasedRandomSequence import BiasedRandomSequence, sample_pair
from ConfigFile import ConfigFile
from RandomSongGen import random_song, tempo_gen, random_chromosome
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

def get_crossover_prob(i, pc=60):
    pc /= 100
    prob = (pc*(1 - pc)**i)*100
    return int(prob)

def init_arg_parser():
    parser = ArgumentParser()
    parser.add_argument('-n', "--new", help="creates new genome", action="store_true")
    parser.add_argument('-s', "--seed", help="specifies seed for new genome", type=int)
    parser.add_argument('-p', "--pid", help="pid for calling code", type=int) 
    return parser.parse_args() 

def alert_parent_program(pid):
    if pid is not None:
        system("kill -CONT " + str(pid))

def write_to_output_file(output_file_name, *songs):
     with open(output_file_name, 'w') as save:
        save.write(str(len(songs)) + '\n')
        for song in songs:
            save.write(str(song) + '\n') 

get_gen_num = lambda song_id, song_count: song_id//song_count

def get_population_sample(config_obj, *songs):
    gen_num = get_gen_num(songs[0].song_id, config_obj.song_count)
    wv = []
    for song in songs:
        if wv == []:
            wv.append(song)
        elif wv[len(wv) - 1].score == song.score:
            continue
        else:
            wv.append(song) 
        
        if len(wv) == config_obj.sample_size:
            break 
        
    write_to_output_file(config_obj.sample_file + "_generation_{}"
                         .format(gen_num), *wv)

def get_avg(*scores):
    return round(sum([score for score in scores])/len(scores)) 

def append_to_graph_file(file_name, gen_num, *value):
    with open(file_name, 'a') as graph:
        graph.write(str(gen_num))
        for i in value:
            graph.write(" " + str(i)) 
        graph.write('\n');

def clear_file(file_name):
    with open(file_name, 'w') as graph:
        graph.write(str(''))

def read_input_file_line(file_obj):
    return tuple(map(int, file_obj.readline().split()))

    
if __name__ == "__main__":
    args = init_arg_parser()
    
    randomizer = GeneticRandomizer(SystemRandom())
    
    logging.basicConfig(filename=LOG_FILE_PATH, level=logging.DEBUG)
    
    if path.exists(CONFIG_FILE_PATH) and path.isfile(CONFIG_FILE_PATH):
       config_file = ConfigFile(CONFIG_FILE_PATH)
    else:
        raise OSError("config file: {}, not found".format(CONFIG_FILE_PATH))

    if args.new: 
        clear_file(LOG_FILE_PATH)
        clear_file(config_file.graph_file)
        seed(args.seed)
        song_list = [random_song(config_file) for i in range(config_file.song_count)]
        save_songs(config_file.save_file, *song_list)
        write_to_output_file(config_file.save_file, *song_list)
        alert_parent_program(args.pid)       
        raise SystemExit  
    else:
        song_list = load_songs(config_file.save_file, config_file)
        flat_song_list = [song.flatten() for song in song_list]
        score_list = []
        diversity_list = []
        with open(config_file.input_file) as save:
            for song in song_list:
                score, diversity = read_input_file_line(save)
                score_list.append(score)
                diversity_list.append(abs(diversity))
                song.score = score * config_file.score_scale_factor
                song.diversity = diversity * config_file.div_scale_factor + 1
            song_list.sort(key=lambda v: v.score//v.diversity, reverse=False)
            for i in range(len(song_list)):
                song_list[i].crossover_chance = get_crossover_prob(i)
            clear_file(config_file.input_file)
    

    get_population_sample(config_file, *song_list)
    logging.info("avg fitness: {}, max fitness: {}, min fitness: {}".format(get_avg(*score_list), max(score_list), min(score_list)))
    gen_num = get_gen_num(song_list[1].song_id, config_file.song_count)
    value_list = [get_avg(*score_list), max(score_list), min(score_list), get_avg(*diversity_list)]
    append_to_graph_file(config_file.graph_file, gen_num, *value_list)

    new_song_list = []
    top_song = min(song_list, key=lambda v: v.score)
    top_song.song_id = (gen_num + 1) * config_file.song_count
    new_song_list.append(top_song)
    song_list = BiasedRandomSequence(*song_list, insert_key=lambda v: v.crossover_chance) 
    

    for i in range(config_file.song_count - 1):
        song1, song2 = sample_pair(song_list)
        c_over_point = randomizer.get_crossover_point(song1, song2)
        song3 = song1.crossover(song2, c_over_point)
        logging.info("songs {} and {} with fitnesses {} {}, crossed over, at {}"
                         .format(song1.song_id, song2.song_id, song1.score, song2.score, c_over_point))
        
        if randomizer.get_prob() <= config_file.mutation_chance:
            if randomizer.get_prob() <= config_file.chromo_delete_prob and len(song3) > 1:
                del_track_id = randomizer.sample_one_item(song3.track_ids)
                song3.chromosome_delete(del_track_id)
                logging.info("song {}, was mutated (chromo delete)".format(song3.song_id))
            elif randomizer.get_prob() <= config_file.chromo_add_prob:
                song3.chromosome_add(random_chromosome(config_file))
                logging.info("song {}, was mutated (chromo add)".format(song3.song_id))
            else:
                meta_data = tempo_gen(config_file)
                delta_mask = randomizer.get_delta_mask(config_file.max_step_size, song3, meta_data)
                song3.mutate(*delta_mask)
                logging.info("song {}, was mutated".format(song3.song_id))

        new_song_list.append(song3)

    logging.debug("song {}, with fitness {}, obj id {}".format(top_song.song_id, top_song.score), id(top_song))
    
    song_list = new_song_list
    write_to_output_file(config_file.save_file, *song_list)
    save_songs(config_file.save_file, *song_list)
    alert_parent_program(args.pid)
    raise SystemExit
