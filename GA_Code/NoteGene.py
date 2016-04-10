"""

 NoteGene.py

  Created on: Feb 10, 2016
      Author: Lee

"""

from copy import copy


class NoteGene:
    """
    >>> gene1 = NoteGene(1,2,3,2,1)
    >>> gene1.__repr__()
    '[1, 2, 3, 2, 1]'
    >>> gene1.__str__()
    '2 3 4'
    >>> gene2 = copy(gene1)
    >>> gene1.__repr__() == gene2.__repr__()
    True
    """

    def __init__(self, *args, max_pause=None, tone_range=None, hold_range=None, safe_mutation=False):
        """
        >>> gene = NoteGene(1,2,3,2,1)
        >>> gene.left_pause_time
        1
        >>> gene.left_hold_time
        2
        >>> gene.tone
        3
        >>> gene.right_hold_time
        2
        >>> gene.right_pause_time
        1
        """
        self.left_pause_time = args[0]
        self.left_hold_time = args[1]
        self.tone = args[2]
        self.right_hold_time = args[3]
        self.right_pause_time = args[4]

        self.max_pause = max_pause//2 + 1
        self.tone_range = divide_range(tone_range)
        self.hold_range = divide_range(hold_range)

        self.safe_mutation_on = safe_mutation

    @property
    def pause_time(self):
        """
        >>> gene = NoteGene(1,2,3,2,1)
        >>> gene.pause_time
        2
        """
        return self.left_pause_time + self.right_pause_time
    
    @property
    def hold_time(self):
        """
        >>> gene = NoteGene(1,2,3,2,1)
        >>> gene.hold_time
        4
        """
        return self.left_hold_time + self.right_hold_time

    def __len__(self):
        """
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(2,2,2,2,2)
        >>> len(gene1)
        2
        >>> len(gene2)
        4
        """
        return self.hold_time
        
    def __str__(self):
        """
        Returns the string representation of a NoteGene, in the format of,
        
        [<pause_time>, <tone>, <hold_time>]

        This is meant to abstract away the two hold and pause times 
        
        >>> gene = NoteGene(1,2,3,2,1)
        >>> str(gene)
        '2 3 4'
        """
        rv = ''
        for item in [self.pause_time, self.tone, self.hold_time]:
            rv += str(item) + ' '
        
        return rv.strip()

    def __repr__(self):
        """
        Returns a representation of a NoteGene, in the format of, 

        [<left_pause>, <left_hold>, <tone>, <right_hold>, <right_pause>]
       
        >>> gene = NoteGene(1,2,3,2,1)
        >>> gene
        [1, 2, 3, 2, 1]
        """
        return str([self.left_pause_time, self.left_hold_time, self.tone,
                    self.right_hold_time, self.right_pause_time])

    def __copy__(self):
        """
        Returns a replica of self, which has a different id,
        via the copy function

        >>> gene1 = NoteGene(1,2,3,4,5)
        >>> gene2 = copy(gene1)
        >>> gene2.right_pause_time
        1
        >>> gene2.right_hold_time
        2
        >>> gene2.tone
        3
        >>> gene2.left_hold_time
        4
        >>> gene2.left_pause_time
        5
        """
        rv = NoteGene(self.right_pause_time, self.right_hold_time,
                      self.tone,
                      self.left_hold_time, self.left_pause_time) 
        rv.max_pause = self.max_pause
        rv.hold_range = self.hold_range
        rv.tone_range = self.tone_range 
        rv.safe_mutation_on = self.safe_mutation_on
        return rv

    def __eq__(self, gene2):
        """
        Determine if two genes are equal
        
        >>> gene1 = NoteGene(1,1,1,1,1)
        >>> gene2 = NoteGene(1,1,1,1,1)
        >>> gene3 = NoteGene(1,1,1,1,2)
        >>> gene1 == gene2
        True
        >>> gene1 == gene3
        False
        """
        return ((self.left_pause_time == gene2.left_pause_time) and
                (self.right_pause_time == gene2.right_pause_time) and
                (self.left_hold_time == gene2.left_hold_time) and
                (self.right_hold_time == gene2.right_hold_time) and
                (self.tone == gene2.tone))
    
    
    def _safe_mutate(self, *delta_mask):
        """
        >>> gene = NoteGene(1, 2, 3, 2, 1)
        >>> gene.mutate(2, 0, -2, 0, 2)
        >>> gene
        [3, 2, 1, 2, 3]
        >>> gene.mutate(2)
        Traceback (most recent call last):
            ...
        TypeError: expected 5 arguments, got 1
        >>> gene.mutate(1,1,1,1,1,1)
        Traceback (most recent call last):
            ...
        TypeError: expected 5 arguments, got 6
        """
        if len(delta_mask) != 5:
            raise TypeError("expected 5 arguments, got {}".format(len(delta_mask)))
        
        self.left_pause_time = to_range(self.left_pause_time + delta_mask[0], range(self.max_pause))
        self.left_hold_time = to_range(self.left_hold_time + delta_mask[1], self.hold_range)
        self.tone = to_range(self.tone + delta_mask[2], self.tone_range)
        self.right_hold_time = to_range(self.right_hold_time + delta_mask[3], self.hold_range)
        self.right_pause_time = to_range(self.right_pause_time + delta_mask[4], range(self.max_pause))

    def _unsafe_mutate(self, *delta_mask):
        if len(delta_mask) != 5:
            raise TypeError("expected 5 arguments, got {}".format(len(delta_mask)))
        
        self.left_pause_time += delta_mask[0]
        self.left_hold_time += delta_mask[1] 
        self.tone += delta_mask[2]
        self.right_hold_time += delta_mask[3]
        self.right_pause_time += delta_mask[4]

    def mutate(self, *delta_mask):
        if self.safe_mutation_on:
            self._safe_mutate(*delta_mask)
        else:
            self._unsafe_mutate(*delta_mask)


    def flatten(self):
        """
        Inputs: None
        Outputs: a list containing a gene's attributes
        in the order detailed in __repr__

        >>> gene = NoteGene(1,1,1,1,1)
        >>> gene.flatten()
        [1, 1, 1, 1, 1]
        >>> type(gene.flatten()) is list
        True
        """
        return [self.left_pause_time, self.left_hold_time, self.tone,
                self.right_hold_time, self.right_pause_time] 


def divide_range(r):
    return range(min(r)//2, max(r)//2 + 1)


def to_range(value, new_range):
    return value % (max(new_range) - min(new_range)) + min(new_range)




        




        



        




