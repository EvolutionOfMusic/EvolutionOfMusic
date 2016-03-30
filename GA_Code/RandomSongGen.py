from threading import Thread, Lock
from random import randrange, seed
from multiprocessing import Pool

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
    
    rv = NoteGene(right_pause_time, right_hold_time, tone,
                    left_hold_time, left_pause_time,
                    max_pause=config_obj.max_pause_time,
                    tone_range=tone_range, hold_range=hold_range,
                    safe_mutation=True)
    return rv

def random_chromosome(config_obj):
    volume = randrange(0,config_obj.max_volume)
    track_id = randrange(0,config_obj.max_track_id)
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
                       tempo=tempo_gen(config_obj)[0])
    


class BatchGen:

    def __init__(self, config_obj):
        self.config = config_obj

    def __call__(self, batch_size):
        """
        Inputs: the number of songs to be created, and the object
        containing all of the data that controls the random genetation
        of songs
        Outputs: a list of size batch_size
        """
        return [random_song(self.config) for i in range(batch_size)]

class BatchMerger:

    def __init__(self):
        self._master_list = []
            
    def __call__(self, batch):
        self._master_list.extend(batch)
        
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


def random_song_improved(p_num, config_obj):
    with Pool(processes=p_num) as pool:
       result = pool.map_async(BatchGen(config_obj),
                               *get_batches(config_obj.song_count),
                               callback=BatchMerger()).get()
    return result[0]
        
def get_batches(total_amount):
    """
    >>> get_batches(599)
    [100, 100, 100, 100, 100, 99]
    >>> get_batches(100)
    [100]
    >>> get_batches(99)
    [99]
    """
    rv = [100] * (total_amount // 100)
    if total_amount - sum(rv) > 0:
        rv.append(total_amount - sum(rv))
    return rv
    

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
    
