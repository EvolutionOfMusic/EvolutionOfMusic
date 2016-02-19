from copy import copy
from math import inf

from NoteGene import NoteGene
#implement fill with zeros functionality
#add song length to save_songs in main


class NoteChromosome:
    """
    >>> gene1 = NoteGene(1,1,1,1,1)
    >>> gene2 = NoteGene(2,2,2,2,2)
    >>> gene3 = NoteGene(3,3,3,3,3)
    >>> gene4 = NoteGene(4,4,4,4,4)
    >>> nc1 = NoteChromosome(gene1,gene2,gene3)
    >>> nc2 = NoteChromosome(gene1,gene2,gene3,gene4, max_len=3)
    >>> nc1[0] == gene1
    True
    >>> print(nc1)
    None None
    2 1 2
    4 2 4
    6 3 6
    >>> nc1
    None
    None
    [1, 1, 1, 1, 1]
    [2, 2, 2, 2, 2]
    [3, 3, 3, 3, 3]
    >>> len(nc1)
    3
    >>> len(nc2)
    3
    >>> nc2 = copy(nc1)
    >>> nc1 == nc2
    True
    >>> nc3 = NoteChromosome(gene1,gene2,gene3,max_len=2,track_id=23,volume=8)
    >>> nc3
    23
    8
    [1, 1, 1, 1, 1]
    [2, 2, 2, 2, 2]
    """
    
    def __init__(self, *genes, track_id=None, volume=None, max_len=inf):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc = NoteChromosome(gene1, gene2, gene3, track_id=10, volume=10)
        >>> nc.track_id
        10
        >>> nc.volume
        10
        """
        if max_len is inf:
            self._gene_list = list(genes)
        elif len(genes) <= max_len:
            self._gene_list = list(genes)
        else:
            self._gene_list = [genes[i] for i in range(max_len)]

        self.track_id = track_id
        self.volume = volume
        self._max_length = max_len

    @property
    def max_length(self):
        return self._max_length

    @max_length.setter
    def max_length(self, new_max_length):
        self._gene_list = self._gene_list[0:new_max_length]
        self._max_length = new_max_length
             
    def __len__(self):
        """
        Returns the number of genes in the Chromosome
        
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc1 = NoteChromosome(gene1, gene2)
        >>> nc2 = NoteChromosome(gene1, gene2, gene3)
        >>> len(nc1)
        2
        >>> len(nc2)
        3
        """
        return len(self._gene_list)

    def __getitem__(self, index):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc = NoteChromosome(gene1,gene2,gene3)
        >>> nc[0] == gene1
        True
        >>> nc[1] == gene2
        True
        >>> nc[2] == gene3
        True
        >>> nc[3]
        Traceback (most recent call last):
            ...
        IndexError: index out of bounds for this chromosome
        """
        try:
            return self._gene_list[index]
        except IndexError:
            raise IndexError("index out of bounds for this chromosome")

    
    def __str__(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> nc = NoteChromosome(gene1, gene2, gene3, volume=1, track_id=2)
        >>> print(nc)
        2 1
        2 1 2
        4 2 4
        6 3 6
        """
        rv = ''
        rv += str(self.track_id) + ' '
        rv += str(self.volume) + '\n'
        for gene in self._gene_list:
            rv += (str(gene) + '\n')
        return rv.strip('\n')

    def __repr__(self):
        """
        >>> gene1 = NoteGene(1,2,3,2,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(4,5,6,5,4)
        >>> nc = NoteChromosome(gene1, gene2, gene3, track_id=0, volume=1)
        >>> nc
        0
        1
        [1, 2, 3, 2, 1]
        [2, 2, 2, 2, 2]
        [4, 5, 6, 5, 4]
        """
        rv = str(self.track_id) + '\n'
        rv += str(self.volume) + '\n'
        for gene in self._gene_list:
            rv += (gene.__repr__() + '\n')
        return rv.strip('\n')

    def __copy__(self):
        """
        Returns of replica of the NoteChromosome

        >>> gene1 = NoteGene(1,2,3,2,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(4,5,6,5,4)
        >>> nc1 = NoteChromosome(gene1, gene2, gene3, track_id=10, volume=9)
        >>> nc2 = copy(nc1)
        >>> nc1 == nc2
        True
        """
        return NoteChromosome(*copy(self._gene_list), max_len=self.max_length,
                              track_id=self.track_id, volume=self.volume)

    def __eq__(self, n_chromosome):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> nc1 = NoteChromosome(gene1,gene2)
        >>> nc2 = NoteChromosome(gene1,gene2)
        >>> nc3 = NoteChromosome(gene2, gene1)
        >>> nc1 == nc2
        True
        >>> nc1 == nc3
        False
        """
        return ((self.max_length == n_chromosome.max_length) and
                (self.track_id == n_chromosome.track_id) and
                (self.volume == n_chromosome.volume) and
                (self._gene_list == n_chromosome._gene_list))

    def split_crossover(self, crossover_point, nchromo):
        """
        inputs:

        crossover_point = the index of the last gene that will be
        included in the first half of the split in the calling NoteChromosome,
        and the second in the input NoteChromosome
    
        nchromo = the input NoteChromosome

        output:
        
        A new NoteChromosome that this the two halves of the calling and input
        NoteChromosomes
    
        
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> gene4 = NoteGene(4,4,4,4,4)
        >>> nc1 = NoteChromosome(gene1,gene2,max_len=2)
        >>> nc2 = NoteChromosome(gene3,gene4,max_len=2)
        >>> nc2
        None
        None
        [3, 3, 3, 3, 3]
        [4, 4, 4, 4, 4]
        >>> nc1.split_crossover(0, nc2)
        None
        None
        [3, 3, 3, 3, 3]
        [4, 4, 4, 4, 4]
        >>> nc1.split_crossover(1, nc2)
        None
        None
        [1, 1, 1, 1, 1]
        [4, 4, 4, 4, 4]
        >>> nc1.split_crossover(2, nc2)
        Traceback (most recent call last):
            ...
        IndexError: crossover point out of bounds
        >>> nc1.split_crossover(0, \"nc2\")
        Traceback (most recent call last):
            ...
        TypeError: only arguments of type NoteChromosome accepted
        """
        if crossover_point >= self.max_length:
            raise IndexError("crossover point out of bounds")

        if type(nchromo) is not NoteChromosome:
            raise TypeError("only arguments of type NoteChromosome accepted")

       
        gene_list = self[:crossover_point] + nchromo[crossover_point:]

        rv = NoteChromosome(*gene_list, track_id=self.track_id,
                              volume=self.volume, max_len=self.max_length)
        
        rv.track_id = self.track_id
        rv.volume = self.volume
        
        return rv 

    def mutate(self, *delta_mask):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> gene3 = NoteGene(3,3,3,3,3)
        >>> gene4 = NoteGene(4,4,4,4,4)
        >>> nc1 = NoteChromosome(gene1,gene2,gene3)
        >>> nc2 = NoteChromosome(gene4)
        >>> nc1
        None
        None
        [1, 1, 1, 1, 1]
        [2, 2, 2, 2, 2]
        [3, 3, 3, 3, 3]
        >>> nc1.mutate(2,2,2,2,2,1,1,1,1,1,0,0,0,0,0)
        >>> nc1
        None
        None
        [3, 3, 3, 3, 3]
        [3, 3, 3, 3, 3]
        [3, 3, 3, 3, 3]
        >>> nc2.mutate(0,-1,-2,-3,-4)
        >>> nc2
        None
        None
        [4, 3, 2, 1, 0]
        >>> nc1.mutate(2,2,2,2,2)
        Traceback (most recent call last):
            ...
        ValueError: delta mask must be of size 15 not 5
        """
        if len(delta_mask) is not len(self)*5:
            raise ValueError("delta mask must be of size {} not {}".format(len(self)*5, len(delta_mask)))

        for i in range(len(self)):
            j = i * 5
            self[i].mutate(*delta_mask[j:j + 5])

