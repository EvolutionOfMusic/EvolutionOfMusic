from SongPersistance import load_songs, save_songs
from BiasedRandomSequence import BiasedRandomSequence, sample_pair
from ConfigFile import ConfigFile
from RandomSongGen import random_song_improved, tempo_gen
from GeneticRandomizer import GeneticRandomizer
from GeneticSong import min_nc_length

from random import SystemRandom, seed, randrange
from argparse import ArgumentParser
from math import inf, sqrt
import sys
from os import system, path
import logging

CONFIG_FILE_PATH = "pyth_main.config"
LOG_FILE_PATH = "main_log.txt"

NUM_THREADS = 4

random_track_id = lambda song, randomizer: randomizer.sample(song.track_ids, 1)[0]

def get_crossover_prob(index, pc=60):
    pc /= 100
    prob = int(100*pc*(1-pc)**index)
    return prob

def init_arg_parser():
    parser = ArgumentParser()
    parser.add_argument('-n', "--new", help="creates new genome", action="store_true")
    parser.add_argument('-s', "--seed", help="specifies seed for new genome", type=int)
    parser.add_argument('-p', "--pid", help="pid for calling code", type=int)
    return parser 

def get_commandline_args():
    return init_arg_parser().parse_args()

def alert_parent_program(pid):
    if pid is not None:
        system("kill -CONT -" + str(pid))

def write_to_output_file(output_file_name, *songs):
     with open(output_file_name, 'w') as save:
        save.write(str(len(songs)) + '\n')
        for song in songs:
            save.write(str(song) + '\n')
            
if __name__ == "__main__":
    args = get_commandline_args()
    
    randomizer = GeneticRandomizer(SystemRandom())
    logging.basicConfig(filename=LOG_FILE_PATH, level=logging.DEBUG)
    
    if path.exists(CONFIG_FILE_PATH) and path.isfile(CONFIG_FILE_PATH):
       config_file = ConfigFile(CONFIG_FILE_PATH)
    else:
        raise OSError("config file: {}, not found".format(CONFIG_FILE_PATH))

    if args.new:
        seed(args.seed)
        song_list = random_song_improved(NUM_THREADS, config_file)
        
        save_songs(config_file.save_file, *song_list)
        write_to_output_file(config_file.save_file, *song_list)
        alert_parent_program(args.pid)       
        raise SystemExit
    
    else:
        song_list = load_songs(config_file.save_file, config_file)

        with open(config_file.input_file) as save:
            for song in song_list:
                song.score = int(save.readline())
            song_list.sort(key=lambda v: v.score, reverse=True)
            for i in range(len(song_list)):
                song_list[i].crossover_chance = get_crossover_prob(i)
                
    song_list = BiasedRandomSequence(*song_list, insert_key=lambda v: v.crossover_chance) 
    new_song_list = []

    for i in range(config_file.song_count):
        song1, song2 = sample_pair(song_list)
        
        song3 = song1.crossover(song2, randomizer.get_crossover_point(song1, song2))
        logging.info("songs {} and {} with fitnesses {} {}, crossed over"
                         .format(song1.song_id, song2.song_id, song1.score, song2.score))
        
        if randomizer.get_prob() <= config_file.mutation_chance:
            meta_data = tempo_gen(config_file)
            delta_mask = randomizer.get_delta_mask(config_file.max_step_size, song3, meta_data)
            song3.mutate(*delta_mask)
            logging.info("song {}, was mutated".format(song3.song_id))
        new_song_list.append(song3)
        
    song_list = new_song_list
    
    write_to_output_file(config_file.save_file, *song_list)
    save_songs(config_file.save_file, *song_list)
    alert_parent_program(args.pid)
    raise SystemExit
