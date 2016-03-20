from copy import copy, deepcopy
from random import randint, seed

from NoteGene import NoteGene
from NoteChromosome import NoteChromosome
from to_range import to_range
       
class GeneticSong:
    """
    >>> gene1 = NoteGene(1,1,1,1,1)
    >>> gene2 = NoteGene(2,2,2,2,2)
    >>> gene3 = NoteGene(3,3,3,3,3)
    >>> gene4 = NoteGene(4,4,4,4,4)
    >>> gene5 = NoteGene(5,5,5,5,5)
    >>> gene6 = NoteGene(6,6,6,6,6)
    >>> gene7 = NoteGene(7,7,7,7,7)
    >>> gene8 = NoteGene(8,8,8,8,8)
    >>> nc1 = NoteChromosome(gene1,gene2,track_id=0)
    >>> nc2 = NoteChromosome(gene3,gene4,track_id=1)
    >>> nc3 = NoteChromosome(gene5,gene6,track_id=2)
    >>> nc4 = NoteChromosome(gene7,gene8,track_id=3)
    >>> song1 = GeneticSong(nc1, nc2)
    >>> song1.song_id
    0
    >>> song2 = GeneticSong(nc3, nc4)
    >>> song2.song_id
    1
    >>> song3 = GeneticSong(nc3, nc4, nc2, max_len=2)
    >>> song3.song_id
    2
    >>> len(song3)
    2
    >>> song1.min_chromo_length
    2
    >>> song1
    0
    0
    0
    None
    [1, 1, 1, 1, 1]
    [2, 2, 2, 2, 2]
    <BLANKLINE>
    1
    None
    [3, 3, 3, 3, 3]
    [4, 4, 4, 4, 4]
    >>> song2
    1
    0
    2
    None
    [5, 5, 5, 5, 5]
    [6, 6, 6, 6, 6]
    <BLANKLINE>
    3
    None
    [7, 7, 7, 7, 7]
    [8, 8, 8, 8, 8]
    >>> print(song1)
    2
    0
    0
    2
    0 None
    2 1 2
    4 2 4
    2
    1 None
    6 3 6
    8 4 8
    >>> song4 = copy(song1)
    >>> song1 == song4
    True
    >>> song4[0] == nc1
    True
    >>> len(song4)
    2
    """
    
    _song_count = 0
    
    def __init__(self, *nchromos, tempo=0, max_len=None, tempo_range=None):
        """
        >>> gene = NoteGene(1,1,1,1,1)
        >>> chromosome = NoteChromosome(gene)
        >>> song = GeneticSong(chromosome, max_len=3, tempo=8)
        >>> song2 = GeneticSong(chromosome)
        >>> song.mutation_chance
        0
        >>> song.crossover_chance
        0
        >>> song.score
        0
        >>> song.max_length
        3
        >>> song.tempo
        8
        """
        
        self._chromosome_dict = {nc.track_id:nc for nc in nchromos[:max_len]}
        
        self._max_length = max_len
        self.tempo_range = tempo_range
        self.tempo = tempo
        if tempo_range is not None:
            self.tempo = to_range(self.tempo, tempo_range)

        self.mutation_chance = 0
        self.crossover_chance = 0
        self.score = 0
	

        self._song_id = type(self)._song_count
        type(self)._song_count += 1

    @property
    def song_id(self):
        return self._song_id
        
        
    @song_id.setter
    def song_id(self, new_id):
        self._song_id = new_id
        type(self)._song_count = new_id + 1
        
    @property
    def max_length(self):
        return self._max_length

    @property
    def min_chromo_length(self):
        nc = min(self._chromosome_dict.values(), key=lambda v: len(v))
        return len(nc)

    @property
    def _chromosome_list(self):
        rv = list(self._chromosome_dict.values())
        rv.sort(key=lambda v: v.track_id)
        return rv

    @property
    def track_ids(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1,track_id=19)
        >>> nc2 = NoteChromosome(gene2,track_id=1919)
        >>> nc3 = NoteChromosome(gene3,track_id=191919)
        >>> song = GeneticSong(nc1,nc2,nc3)
        >>> song.track_ids == {19, 1919, 191919}
        True
        """
        return {nc.track_id for nc in self._chromosome_list}

    @property
    def num_genes(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1,gene2,track_id=19)
        >>> nc2 = NoteChromosome(gene3,track_id=1919)
        >>> song = GeneticSong(nc1, nc2)
        >>> song.num_genes
        3
        """
        return sum([len(nc) for nc in self._chromosome_dict.values()])
        
    def __eq__(self, gsong):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> nc1 = NoteChromosome(gene1,gene2)
        >>> nc2 = NoteChromosome(gene1)
        >>> song1 = GeneticSong(nc1)
        >>> song2 = GeneticSong(nc1)
        >>> song3 = GeneticSong(nc2)
        >>> song4 = GeneticSong(nc1,tempo=8)
        >>> song1 == song2
        True
        >>> song1 == song3
        False
        >>> song1 == song4
        False
        """
        if type(gsong) is not GeneticSong:
            return False

        return ((self._chromosome_list == gsong._chromosome_list) and
                (self.mutation_chance == gsong.mutation_chance) and
                (self.crossover_chance == gsong.mutation_chance) and
                (self.tempo == gsong.tempo) and
                (self.score == gsong.score))

    def __repr__(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> gene4 = NoteGene(4,4,4,4,4)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id=1)
        >>> nc2 = NoteChromosome(gene3, gene4, track_id=2)
        >>> song = GeneticSong(nc1, nc2, tempo=19)
        >>> song
        14
        19
        1
        None
        [1, 1, 1, 1, 1]
        [2, 2, 2, 2, 2]
        <BLANKLINE>
        2
        None
        [3, 3, 3, 3, 3]
        [4, 4, 4, 4, 4]
        """
        rv = str(self.song_id) + '\n'
        rv += str(self.tempo) + '\n'
        
        for chromosome in self._chromosome_list:
            rv += (chromosome.__repr__() + "\n\n")
        return rv.strip("\n\n")

    def __str__(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> gene4 = NoteGene(4,4,4,4,4)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id=0)
        >>> nc2 = NoteChromosome(gene3, gene4, track_id=1)
        >>> song = GeneticSong(nc1, nc2, tempo=1)
        >>> print(song)
        2
        1
        15
        2
        0 None
        2 1 2
        4 2 4
        2
        1 None
        6 3 6
        8 4 8
        """
        rv = str(len(self)) + '\n'
        rv += str(self.tempo) + '\n'
        rv += str(self.song_id) + '\n'
        for chromosome in self._chromosome_list:
            rv += (str(chromosome) + "\n")
        return rv.strip('\n') 

    def __copy__(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> nc1 = NoteChromosome(gene1)
        >>> song1 = GeneticSong(nc1)
        >>> song2 = copy(song1)
        >>> song1 == song2
        True
        """
        rv = GeneticSong(*copy(self._chromosome_list), max_len=self.max_length)
        rv.mutation_chance = self.mutation_chance
        rv.crossover_chance = self.crossover_chance
        rv.score = self.score
        return rv

    def __getitem__(self, track_id):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id=0)
        >>> nc2 = NoteChromosome(gene3, track_id=1)
        >>> song = GeneticSong(nc1, nc2)
        >>> song[0] == nc1
        True
        >>> song[1] == nc2
        True
        >>> song[2]
        Traceback (most recent call last):
            ...
        KeyError: 'track id does not exist'
        """
        if track_id not in self._chromosome_dict:
           raise KeyError("track id does not exist") 
        
        return self._chromosome_dict[track_id]
        

    def __len__(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id=0)
        >>> nc2 = NoteChromosome(gene3, track_id=1)
        >>> song = GeneticSong(nc1, nc2)
        >>> len(song)
        2
        """
        return len(self._chromosome_dict)
    
    def crossover(self, song, crossover_point):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> gene4 = NoteGene(4,4,4,4,4)
        >>> gene5 = NoteGene(5,5,5,5,5)
        >>> gene6 = NoteGene(6,6,6,6,6)
        >>> gene7 = NoteGene(7,7,7,7,7)
        >>> gene8 = NoteGene(8,8,8,8,8)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id=0)
        >>> nc2 = NoteChromosome(gene3, gene4, track_id=1)
        >>> nc3 = NoteChromosome(gene5, gene6, track_id=0)
        >>> nc4 = NoteChromosome(gene7, gene8, track_id=2)
        >>> song1 = GeneticSong(nc1, nc2)
        >>> song2 = GeneticSong(nc3, nc4)
        >>> song3 = GeneticSong(nc1)
        >>> song4 = GeneticSong(nc3)
        >>> song5 = GeneticSong(nc2)
        >>> song6 = GeneticSong(nc4)
        >>> song1.crossover(song2, 1)
        24
        0
        0
        None
        [1, 1, 1, 1, 1]
        [6, 6, 6, 6, 6]
        <BLANKLINE>
        1
        None
        [3, 3, 3, 3, 3]
        [4, 4, 4, 4, 4]
        <BLANKLINE>
        2
        None
        [7, 7, 7, 7, 7]
        [8, 8, 8, 8, 8]
        >>> song3.crossover(song4, 1)
        25
        0
        0
        None
        [1, 1, 1, 1, 1]
        [6, 6, 6, 6, 6]
        >>> song5.crossover(song6, 1)
        26
        0
        1
        None
        [3, 3, 3, 3, 3]
        [4, 4, 4, 4, 4]
        <BLANKLINE>
        2
        None
        [7, 7, 7, 7, 7]
        [8, 8, 8, 8, 8]
        """
        common_track_ids = self.track_ids.intersection(song.track_ids)
        individual_track_ids = set_subtract(self.track_ids, song.track_ids)
        
        new_chromosome_list = []

        new_chromosome_list = [self[track_id].split_crossover(crossover_point, song[track_id])
                               for track_id in common_track_ids]

        for track_id in individual_track_ids:
            try:
                new_chromosome_list.append(deepcopy(self[track_id]))
            except KeyError:
                new_chromosome_list.append(deepcopy(song[track_id]))
                
        return GeneticSong(*new_chromosome_list, max_len=self.max_length)

    def mutate(self, *delta_mask):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> gene4 = NoteGene(4,4,4,4,4)
        >>> gene5 = NoteGene(5,5,5,5,5)
        >>> gene6 = NoteGene(6,6,6,6,6)
        >>> gene7 = NoteGene(7,7,7,7,7)
        >>> gene8 = NoteGene(8,8,8,8,8)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id = 1)
        >>> nc2 = NoteChromosome(gene3, gene4, track_id = 3)
        >>> nc3 = NoteChromosome(gene5, track_id=0)
        >>> nc4 = NoteChromosome(gene6, track_id=2)
        >>> nc5 = NoteChromosome(gene7, track_id=4)
        >>> nc6 = NoteChromosome(gene8, track_id=6)
        >>> song1 = GeneticSong(nc1, nc2)
        >>> song1.song_id = 1
        >>> song2 = GeneticSong(nc3, nc4, nc5, nc6)
        >>> song2.song_id = 19
        >>> song1.mutate(0,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,-1,-1,-1,-1,-1)
        >>> song1
        1
        0
        1
        None
        [3, 3, 3, 3, 3]
        [3, 3, 3, 3, 3]
        <BLANKLINE>
        3
        None
        [3, 3, 3, 3, 3]
        [3, 3, 3, 3, 3]
        >>> song2.song_id == 19
        True
        >>> song2.mutate(40,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5)
        >>> song2
        19
        40
        0
        None
        [3, 3, 3, 3, 3]
        <BLANKLINE>
        2
        None
        [3, 3, 3, 3, 3]
        <BLANKLINE>
        4
        None
        [3, 3, 3, 3, 3]
        <BLANKLINE>
        6
        None
        [3, 3, 3, 3, 3]
        >>> song2.mutate(1,1,1)
        Traceback (most recent call last):
            ...
        ValueError: Expecting delta mask of size 21, got 3
        """
        if len(delta_mask) != (self.num_genes * 5 + 1):
            raise ValueError("Expecting delta mask of size {}, got {}"
                             .format(self.num_genes * 5 + 1, len(delta_mask)))
        self.tempo += delta_mask[0]
        if self.tempo_range is not None:
            self.tempo = to_range(self.tempo, self.tempo_range)

        start_index = 1
        for nc in self._chromosome_dict.values():
            end_index = to_gene_index(len(nc)) + start_index
            nc.mutate(*delta_mask[start_index:end_index])
            start_index = end_index
        
    def chromosome_delete(self, track_id):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> nc1 = NoteChromosome(gene1,track_id=0)
        >>> nc2 = NoteChromosome(gene2,track_id=1)
        >>> song = GeneticSong(nc1,nc2)
        >>> song.chromosome_delete(track_id=0) 
        >>> song
        17
        0
        1
        None
        [2, 2, 2, 2, 2]
        >>> song.chromosome_delete(track_id=1)
        >>> song
        17
        0
        >>> song.chromosome_delete(track_id=1)
        Traceback (most recent call last):
            ...
        KeyError: 'track_id 1 does not exist'
        """
        if track_id not in self.track_ids:
            raise KeyError("track_id {} does not exist".format(track_id))
        
        self._chromosome_dict.pop(track_id)

    def chromosome_add(self, chromosome):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1,track_id=0)
        >>> nc2 = NoteChromosome(gene2,track_id=1)
        >>> nc3 = NoteChromosome(gene3,track_id=2)
        >>> song = GeneticSong(nc1,nc2,max_len=3)
        >>> len(song)
        2
        >>> song.chromosome_add(nc3)
        >>> len(song)
        3
        >>> song
        16
        0
        0
        None
        [1, 1, 1, 1, 1]
        <BLANKLINE>
        1
        None
        [2, 2, 2, 2, 2]
        <BLANKLINE>
        2
        None
        [3, 3, 3, 3, 3]
        >>> song.chromosome_add(4)
        Traceback (most recent call last):
            ...
        ValueError: argument must be of type NoteChromosome
        >>> song.chromosome_add(nc3)
        Traceback (most recent call last):
            ...
        IndexError: max song length has been reached
        """
        if type(chromosome) is not NoteChromosome:
            raise ValueError("argument must be of type NoteChromosome")
        
        if len(self) is self.max_length:
            raise IndexError("max song length has been reached")

        self._chromosome_dict[chromosome.track_id] = chromosome

    def flatten(self):
        """
        Input: None
        Output: a list of flattened NoteChromosomes

        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1, gene2, track_id=1)
        >>> nc2 = NoteChromosome(gene3, track_id=2)
        >>> song = GeneticSong(nc1, nc2)
        >>> song.flatten()
        [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3]
        """
        rv = []
        for nc in self._chromosome_dict.values():
            rv.extend(nc.flatten())
        return rv
            
def set_subtract(set1, set2):
    """
    >>> set1 = {1,2,3,4}
    >>> set2 = {1,2,3,4,5,7}
    >>> set3 = {1,2,3,4}
    >>> set4 = {1,2,3}
    >>> set_subtract(set1, set2) == {5,7}
    True
    >>> set_subtract(set1, set3)
    set()
    >>> set_subtract(set4, set1)
    {4}
    """
    return set1.union(set2) - set1.intersection(set2)

def min_nc_length(song1, song2):
    return min(song1.min_chromo_length,
               song2.min_chromo_length)

to_gene_index = lambda index: index * 5
