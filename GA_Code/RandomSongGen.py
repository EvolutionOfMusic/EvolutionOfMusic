from threading import Thread, Lock
from random import randrange, seed

from ConfigFile import ConfigFile
from NoteGene import NoteGene
from NoteChromosome import NoteChromosome
from GeneticSong import GeneticSong

def random_gene(config_obj):
    right_pause_time = randrange(0, config_obj.max_pause_time//2 + 1)
    right_hold_time = randrange(1, config_obj.max_hold_time//2 + 1)
    tone = randrange(config_obj.min_note, config_obj.max_note + 1)
    left_hold_time = randrange(0, config_obj.max_hold_time//2 + 1)
    left_pause_time = randrange(1, config_obj.max_pause_time//2 + 1)

    tone_range = range(config_obj.min_note, config_obj.max_note + 1)
    hold_range = range(config_obj.min_hold_time, config_obj.max_hold_time + 1)
    
    return NoteGene(right_pause_time, right_hold_time, tone,
                    left_hold_time, left_pause_time,
                    max_pause=config_obj.max_pause_time,
                    tone_range=tone_range, hold_range=hold_range)

def random_chromosome(config_obj):
    volume = randrange(0,config_obj.max_volume)
    #track_id = randrange(0,config_obj.max_track_id)
    track_id = 1
    gene_list = []
    for i in range(config_obj.chromo_length):
        gene_list.append(random_gene(config_obj))
    return NoteChromosome(*gene_list, track_id=track_id, volume=volume,
                          max_len=config_obj.chromo_length)

random_tempo = lambda min_t, max_t: randrange(max_t) + min_t

def random_song(config_obj):
    chromo_list = []
    for i in range(config_obj.song_length):
        chromo_list.append(random_chromosome(config_obj))
    return GeneticSong(*chromo_list, max_len=config_obj.song_length,
                       tempo=random_tempo(config_obj.min_tempo, config_obj.max_tempo))


class ParallelSongGen(Thread):

    def __init__(self, config_file, lock, shared_list):
        Thread.__init__(self)
        self._config_file = config_file
        self._lock = lock
        self._shared_list = shared_list
        

    def run(self):
        global_list = []
        lock = Lock()

        song = random_song(self._config_file)
            
        self._lock.acquire()
        self._shared_list.append(song)
        self._lock.release()


def random_song_parallel(config_file):
    my_lock = Lock()
    global_list = []
        
    threads = [ParallelSongGen(config_file, my_lock, global_list) for i in range(config_file.song_count)]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()

    return global_list
        

def tempo_gen(config):
    return [randrange(config.min_tempo, config.max_tempo)]
    
