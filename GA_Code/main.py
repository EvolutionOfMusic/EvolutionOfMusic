from NoteGene import NoteGene
from NoteChromosome import NoteChromosome
from GeneticSong import GeneticSong
from BiasedRandomSequence import BiasedRandomSequence, sample_pair
from ConfigFile import ConfigFile

from random import SystemRandom, seed, randrange
from argparse import ArgumentParser
from math import inf, sqrt
import sys
from os import system, path


CONFIG_FILE_PATH = "pyth_main.config"

def random_gene(config_obj):
    right_pause_time = randrange(0, config_obj.max_pause_time//2 + 1)
    right_hold_time = randrange(0, config_obj.max_hold_time//2 + 1)
    tone = randrange(config_obj.min_note, config_obj.max_note + 1)
    left_hold_time = randrange(0, config_obj.max_hold_time//2 + 1)
    left_pause_time = randrange(0, config_obj.max_pause_time//2 + 1)
    
    return NoteGene(right_pause_time, right_hold_time, tone,
                    left_hold_time, left_pause_time)

def random_chromosome(config_obj):
    volume = randrange(0,config_obj.max_volume)
    track_id = randrange(0,config_obj.max_track_id)
    gene_list = []
    for i in range(config_obj.chromo_length):
        gene_list.append(random_gene(config_obj))
    return NoteChromosome(*gene_list, track_id=track_id, volume=volume)

random_tempo = lambda min_t, max_t: randrange(max_t) + min_t

def random_song(config_obj):
    chromo_list = []
    for i in range(config_obj.song_length):
        chromo_list.append(random_chromosome(config_obj))
    return GeneticSong(*chromo_list, max_len=config_obj.song_length,
                       tempo=random_tempo(config_obj.min_tempo, config_obj.max_tempo))

def save_songs(save_file, *songs, delimeter='*'):
    with open("genetic_" + save_file, 'w+') as sav_file:
        song_string = ''
        for song in songs:
            song_string += (song.__repr__() + '\n{}\n'.format(delimeter))

        song_string = song_string.strip('\n{}\n'.format(delimeter))
        sav_file.write(song_string)

def gene_from_string(gene_string):
    """
    >>> gene1 = NoteGene(1,2,3,2,1)
    >>> gene1
    [1, 2, 3, 2, 1]
    >>> gene2 = gene_from_string("[1, 2, 3, 2, 1]")
    >>> gene1 == gene2
    True
    """
    param_list = gene_string.replace('[', '').replace(']', '').split(',')
    param_list = list(map(int, param_list))

    return NoteGene(param_list[0], param_list[1], param_list[2], param_list[3],
                    param_list[4])

def chromosome_from_string(chromo_string):
    """
    >>> gene1 = NoteGene(1,1,1,1,1)
    >>> gene2 = NoteGene(2,2,2,2,2)
    >>> nc1 = NoteChromosome(gene1, gene2, track_id=0, volume=1)
    >>> nc2 = chromosome_from_string("0\\n1\\n[1, 1, 1, 1, 1]\\n[2, 2, 2, 2, 2]")
    >>> nc1 == nc2
    True
    """
    track_id, volume = map(int, chromo_string.split('\n')[:2])
    
    param_list = chromo_string.split('\n')[2:]
    gene_list = []
    for param in param_list:
        gene_list.append(gene_from_string(param))
    return NoteChromosome(*gene_list, track_id=track_id, volume=volume)

def song_from_string(song_string):
    """
    >>> gene1 = NoteGene(1,1,1,1,1)
    >>> gene2 = NoteGene(2,2,2,2,2)
    >>> gene3 = NoteGene(3,3,3,3,3)
    >>> gene4 = NoteGene(4,4,4,4,4)
    >>> nc1 = NoteChromosome(gene1,gene2,track_id=0,volume=1)
    >>> nc2 = NoteChromosome(gene3,gene4,track_id=2,volume=3)
    >>> song1 = GeneticSong(nc1, nc2)
    >>> song2 = song_from_string(song1.__repr__())
    >>> song1 == song2
    True
    """
    meta_data_list = song_string.split('\n')[0:2]  
    song_id, tempo = map(int, meta_data_list)
    chromo_strings = song_string.split('\n', 2)[-1].replace('\n\n', '*').split('*')

    chromo_list = map(chromosome_from_string, chromo_strings)

    rv = GeneticSong(*chromo_list)
    rv.song_id = song_id
    rv.tempo = tempo
    
    return rv

def load_songs(load_file, delimeter='*'):
    with open("genetic_" + load_file) as file_obj:
        rv = []
        file_contents = file_obj.read().split('\n{}\n'.format(delimeter))

        for song_string in file_contents:
            rv.append(song_from_string(song_string))
        return rv

def get_crossover_prob(score, total_score):
    return int(100 * (score/total_score))

def get_mutation_prob(crossover_prob):
    return sqrt(crossover_prob)

def init_arg_parser():
    parser = ArgumentParser()
    parser.add_argument('-n', "--new", help="creates new genome", action="store_true")
    parser.add_argument('-s', "--seed", help="specifies seed for new genome", type=int)
    parser.add_argument('-p', "--pid", help="pid for assciated c code", type=int)
    return parser 

def get_commandline_args():
    return init_arg_parser().parse_args()

def alert_parent_program(pid):
    if pid is not None:
        system("kill -CONT -" + str(pid))

def write_to_output_file(output_file_name, *songs):
     with open(output_file_name, 'w') as save:
        save.write(len(songs) + '\n')
        for song in songs:
            save.write(str(song) + '\n')

        
#these should be a class
get_prob = lambda randomozer: randomizer.randrange(0, 100)

random_track_id = lambda song, randomizer: randomizer.sample(song.track_ids, 1)[0]

random_crossover_point = lambda chromo_len, randomizer: randomizer.randrange(chromo_len)

random_delta_mask = lambda max_step_size, randomizer, song: (randomizer.randrange(max_step_size + 1) for i in range(chromo_len*len(song)*5))

if __name__ == "__main__":
    args = get_commandline_args()
    
    randomizer = SystemRandom()
    
    if path.exists(CONFIG_FILE_PATH) and path.isfile(CONFIG_FILE_PATH):
       config_file = ConfigFile(CONFIG_FILE_PATH)
    else:
        raise OSError("config file: {}, not found".format(CONFIG_FILE_PATH))

    if args.new:
        song_list = []
        seed(args.seed)
        for i in range(config_file.song_count):
            song_list.append(random_song(config_file))
            
        save_songs(config_file.save_file, *song_list)
        write_to_output_file(config_file.save, *song_list)
        alert_parent_program(args.pid)       
        raise SystemExit
    
    else:
        song_list = load_songs(genetic_load)

        with open(config_file.input_file) as save:
            total_score = int(save.readline())
            for song in song_list:
                song.score = int(save.readline())
                song.crossover_chance = get_crossover_prob(song.score, total_score)
                song.mutation_chance = get_mutation_prob(song.crossover_chance)

                
    song_list = BiasedRandomSequence(*song_list, insert_key=lambda v: v.crossover_chance) 
    new_song_list = []

    
    for i in range(len(song_list)):
        song1, song2 = sample_pair(song_list)
        song3 = song1.crossover(song2, random_crossover_point(config_file.chromo_length, randomizer))

        if song2.mutation_chance <= get_prob(randomizer):
            delta_mask = random_delta_mask(config.max_step_size, randomizer, song3)
            song3.mutate(*delta_mask)

        new_song_list.append(song3)
        
    song_list = new_song_list

    write_to_output_file(config.save_file, *song_list)
    save_songs(config.save_file, *song_list)
    alert_parent_program(args.pid)
    raise SystemExit
