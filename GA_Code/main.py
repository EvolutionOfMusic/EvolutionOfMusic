from NoteGene import NoteGene
from NoteChromosome import NoteChromosome
from GeneticSong import GeneticSong
from BiasedRandomSequence import BiasedRandomSequence, sample_pair

from random import SystemRandom, seed, randrange
from math import inf, sqrt
import sys
import os


CONFIG_FILE_PATH = "pyth_main.config"

def random_gene(max_hold_time=10, max_pause_time=10):
    """
    >>> gene1 = random_gene()
    >>> gene2 = random_gene(max_hold_time=20, max_pause_time=5)
    >>> gene1 == gene2
    False
    >>> gene2.hold_time <= 20
    True
    >>> gene2.hold_time > 20
    False
    >>> gene2.pause_time <= 5
    True
    >>> gene2.pause_time > 5
    False
    """
    right_pause_time = randrange(0, max_pause_time//2)
    right_hold_time = randrange(0, max_hold_time//2)
    tone = randrange(0, 96)
    left_hold_time = randrange(0, max_hold_time//2)
    left_pause_time = randrange(0, max_pause_time//2)
    
    return NoteGene(right_pause_time, right_hold_time, tone,
                    left_hold_time, left_pause_time)

def random_chromosome(length, max_hold=10, max_pause=10, max_vol=10, max_id=10):
    """
    >>> nc1 = random_chromosome(length=3)
    >>> nc2 = random_chromosome(length=10)
    >>> nc1 == nc2
    False
    >>> len(nc1)
    3
    >>> len(nc2)
    10
    """
    volume = randrange(0,max_vol)
    track_id = randrange(0,max_id)
    gene_list = []
    for i in range(length):
        gene_list.append(random_gene(max_hold, max_pause))
    return NoteChromosome(*gene_list, track_id=track_id, volume=volume)

def random_song(song_len, chromo_len=10, max_hold=10, max_pause=10):
    """
    >>> song1 = random_song(song_len=3)
    >>> song2 = random_song(song_len=2)
    >>> song1 == song2
    False
    >>> len(song1)
    3
    >>> len(song2)
    2
    """
    chromo_list = []
    for i in range(song_len):
        chromo_list.append(random_chromosome(chromo_len, max_hold, max_pause))
    return GeneticSong(*chromo_list, max_len=song_len)

def save_songs(save_file_obj, *songs, delimeter='*'):
    song_string = ''
    for song in songs:
        song_string += (song.__repr__() + '\n{}\n'.format(delimeter))

    song_string = song_string.strip('\n{}\n'.format(delimeter))
    save_file_obj.write(song_string)

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
    meta_data_list = song_string.split('\n')[0:4]  
    song_id, score, crossover_chance, mutation_chance = map(int, meta_data_list)
    chromo_strings = song_string.split('\n', 4)[-1].replace('\n\n', '*').split('*')

    chromo_list = map(chromosome_from_string, chromo_strings)

    rv = GeneticSong(*chromo_list)
    rv.score = score
    rv.crossover_chance = crossover_chance
    rv.mutation_chance = mutation_chance
    rv.song_id = song_id
    
    return rv

def load_songs(file_obj, delimeter='*'):
    rv = []
    file_contents = file_obj.read().split('\n{}\n'.format(delimeter))

    for song_string in file_contents:
        rv.append(song_from_string(song_string))
    return rv

def get_crossover_prob(score, total_score):
    return int(100 * (score/total_score))

def get_mutation_prob(crossover_prob):
    return sqrt(crossover_prob)

def get_commandline_arguments():
    if sys.argv[1] == '-n':
        create_new_genome = True
        songs_graded = False
        seed(int(sys.argv[2]))
    elif sys.argv[1] == '-g':
        create_new_genome = False
        songs_graded = True
    else:
        raise ValueError("main.py missing one argument")

    return create_new_genome, songs_graded

get_prob = lambda randomozer: randomizer.randrange(0, 100)

random_track_id = lambda song, randomizer: randomizer.sample(song.track_ids, 1)[0]

random_crossover_point = lambda chromo_len, randomizer: randomizer.randrange(chromo_len)

random_delta_mask = lambda max_step_size, randomizer, song: (randomizer.randrange(max_step_size + 1) for i in range(chromo_len*len(song)*5))

if __name__ == "__main__":

    create_new_genome, songs_graded = get_commandline_arguments()
    randomizer = SystemRandom()
    
    if os.path.exists(CONFIG_FILE_PATH) and os.path.isfile(CONFIG_FILE_PATH):
        with open(CONFIG_FILE_PATH) as gene_config:
            #to do: clean this up and have errors and functions for config file
            save_file = gene_config.readline().strip("save file: ").strip('\n')
            input_file = gene_config.readline().strip("input file: ").strip('\n')
            num_songs = int(gene_config.readline().strip("song count: "))
            song_len = int(gene_config.readline().strip("song length: "))
            chromo_len = int(gene_config.readline().strip("chromo length: "))
            max_hold_time = int(gene_config.readline().strip("max hold time: "))
            max_pause_time = int(gene_config.readline().strip("max pause time: "))
            chromo_delete_prob = float(gene_config.readline().strip("chromo delete prob: "))
            max_step_size = int(gene_config.readline().strip("max step size: "))
    else:
        raise OSError("config file: {}, not found".format(CONFIG_FILE_PATH))

    if create_new_genome:
              
        song_list = []
        for i in range(num_songs):
            r_song = random_song(song_len, chromo_len, max_hold_time, max_pause_time)
            song_list.append(r_song)
        
        with open("genetic_" + save_file, 'w+') as genetic_sav:
            save_songs(genetic_sav, *song_list)
    else:
        with open("genetic_" + save_file) as genetic_load:
            song_list = load_songs(genetic_load)
    
    if songs_graded:
        with open(input_file) as save:
            total_score = int(save.readline())
            for song in song_list:
                song.score = int(save.readline())
                song.crossover_chance = get_crossover_prob(song.score, total_score)
                song.mutation_chance = get_mutation_prob(song.crossover_chance)
    else:
        with open(save_file, 'w+') as save:
            for song in song_list:
                save.write(str(song) + '\n')
               
        raise SystemExit
    
    song_list = BiasedRandomSequence(*song_list, insert_key=lambda v: v.crossover_chance) 
    new_song_list = []

    
    for i in range(len(song_list)):
        
        song1, song2 = sample_pair(song_list)
        
    
        song3 = song1.crossover(song2, random_crossover_point(chromo_len, randomizer))

        
        if song2.mutation_chance <= get_prob(randomizer):
            delta_mask = random_delta_mask(max_step_size, randomizer, song3)
            song3.mutate(*delta_mask)

        
        new_song_list.append(song3)
        
   
    song_list = new_song_list

    with open(save_file, 'w') as save:
        for song in song_list:
            save.write(str(song) + '\n')

    with open(save_file + "_genetic", 'w') as genetic_save:
        save_songs(genetic_save, *song_list)
    
    raise SystemExit
