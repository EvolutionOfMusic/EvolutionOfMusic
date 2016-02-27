from threading import Thread, Lock

from ConfigFile import ConfigFile
from main import random_gene
from NoteChromosome import NoteChromosome

class ParallelChromoGen(Thread):
    _gene_list = []
    _gene_lock = Lock()
    _num_notes = 0 
    
    def __init__(self, config_name):
        Thread.__init__(self)
        self._config_file = ConfigFile(config_name)
        type(self)._num_notes = self._config_file.chromo_length
    
    def run(self):
        gene = random_gene(self._config_file)
        type(self)._gene_lock.acquire()
        if (type(self)._num_notes - len(gene)) >= 0:
            type(self)._num_notes -= len(gene)
            type(self)._gene_list.append(gene)
        type(self)._gene_lock.release()
        
    def result(self):
        return NoteChromosome(*type(self)._gene_list)


class ParallelSongGen(Thread):
    _chromo_list = []
    _chromo_list_lock = Lock()

    def __init__(self, config_name):
        Thread.__init__(self)
        self._config_file = ConfigFile(config_name)

    def run(self):
        sub_threads = [ParallelChromoGen(config_name) for i in range(self._config_file)]
        
if __name__ == "__main__":
    threads = [ParallelChromoGen("pyth_main.config") for i in range(10000)]

    threads[0].num_notes = 160000
    
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()

    print(threads[0].result())
