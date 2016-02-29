from threading import Thread, Lock
from random import randrange, seed

from ConfigFile import ConfigFile
from main import random_gene
from main import random_tempo
from NoteChromosome import NoteChromosome
from GeneticSong import GeneticSong

class ParallelChromoGen(Thread):
    _gene_list = []
    _gene_lock = Lock()
    
    def __init__(self, config_name):
        Thread.__init__(self)
        self._config_file = ConfigFile(config_name)
    
    def run(self):
        gene = random_gene(self._config_file)
        type(self)._gene_lock.acquire()
        type(self)._gene_list.append(gene)
        type(self)._gene_lock.release()
        
    def result(self):
        volume = randrange(0, self._config_file.max_volume)
        track_id = randrange(0, self._config_file.max_track_id)
        return NoteChromosome(*type(self)._gene_list, volume=volume, track_id=track_id,
                              max_len=self._config_file.chromo_length)


class ParallelSongGen(Thread):
    _chromo_list = []
    _chromo_lock = Lock()

    def __init__(self, config_name):
        Thread.__init__(self)
        self._config_file = ConfigFile(config_name)
        self._config_name = config_name
        self._chromosome_list = []

    def run(self):
        sub_threads = [ParallelChromoGen(self._config_name) for i in range(self._config_file.chromo_length)]

        for thread in sub_threads:
            thread.start()
        for thread in sub_threads:
            thread.join()

        type(self)._chromo_lock.acquire()
        # print(sub_threads[0].result())
        type(self)._chromo_list.append(sub_threads[0].result())
        type(self)._chromo_lock.release()

    def result(self):
        return GeneticSong(*type(self)._chromo_list, max_len=self._config_file.song_length,
                       tempo=random_tempo(self._config_file.min_tempo, self._config_file.max_tempo))

    
        
        
if __name__ == "__main__":
    #seed(666)
    threads = [ParallelSongGen("pyth_main.config") for i in range(10)]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    #print(threads[0].result())
