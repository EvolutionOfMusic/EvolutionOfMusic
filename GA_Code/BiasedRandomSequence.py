from random import SystemRandom


class BiasedRandomSequence:
    """
    A list-like type that facilitates random sampling based on an items
    probability of being chosen.

    The probability that an item will be chosen is converted into a range
    that starts at the ends of the range of the item that came before it.

    Given an item with, value = 12 and prob = 22

    If there are no other objects in the sequence then the range, reffered to
    as the probability index, that can be depicted as follows:

    [(0, 1, 2, 3,... 21):12]

    Appending an item with, value = 7 and prob = 8,
    results in the following sequence:

    [(0, 1, 2, 3,... 21):12, (22, 23, 24,..., 30):8]    

    >>> my_list = BiasedRandomSequence()
    >>> prob, value = 50, 3
    >>> my_list.append(prob, value)
    >>> my_list[0]
    3
    >>> my_list.append(50, 6)
    >>> my_list
    [3, 6]
    >>> len(my_list)
    2
    >>> my_list.random_get() in [3, 6] 
    True
    """
    def __init__(self, *new_items, insert_key=None):
        """
        Input: a sequence of items, and a function that determines their
        probablities of being chosen
        """
        self._data_dict = dict()
        self._index_to_range_dict = dict()
        self._max_prob_index = 0
        self._randomizer = SystemRandom()

        if insert_key is not None:
            for item in new_items:
                self.append(insert_key(item), item)
            

    @property
    def max_index(self):
        """
        Input: None
        Output: the index of the most recently appended item
        """
        return len(self) - 1

    def __len__(self):
        return len(self._data_dict)

    
    def __repr__(self):
        """
        Input: None
        OUtput: the python representation of the sequence
        
        >>> my_list = BiasedRandomSequence()
        >>> my_list.append(10, 1)
        >>> my_list.append(20, 2)
        >>> my_list.append(30, 3)
        >>> my_list.append(30, 4)
        >>> my_list
        [1, 2, 3, 4]
        """
        return str([self[i] for i in range(len(self))])
        
    def __getitem__(self, index):
        """
        Input: a list index
        Output: the item at that index, if one exists
        
        >>> my_list = BiasedRandomSequence()
        >>> my_list.append(10, 1)
        >>> my_list.append(20, 2)
        >>> my_list.append(30, 3)
        >>> my_list.append(30, 4)
        >>> my_list[0]
        1
        >>> my_list[1]
        2
        >>> my_list[4]
        Traceback (most recent call last):
            ...
        IndexError: index out of bounds
        """
        if index >= len(self):
            raise IndexError("index out of bounds")
        
        return self._data_dict[self._index_to_range_dict[index]]

    def __iter__(self):
        """
        Input: None
        Output: an iterator that walks down the sequence,
        returning items in the order they were added
        """
        return BRSequenceIterator(self)

    def _prob_to_range(self, prob):
        """
        Input: a probability between 0 and 100
        Output: a range starting at the _max_prob_index and
        ending at prob + self._max_prob_index
        """
        return range(self._max_prob_index, prob + self._max_prob_index)
    
    def append(self, prob, value):
        """
        Input: a probability between 0 and 100, and a value that has probablity prob
        of being chosen from the sequence
        Output: None 
        """
        if prob > 0:
            self._data_dict[self._prob_to_range(prob)] = value
            self._index_to_range_dict[self.max_index] = self._prob_to_range(prob)
            self._max_prob_index += prob
        
    def random_get(self):
        """
        Input: None
        Output: returns a value, based on that values probability of being
        chosen
        """
        prob_index = self._randomizer.randrange(self._max_prob_index)
        for key in self._data_dict.keys():
            if prob_index in key:
                return self._data_dict[key]

def sample_pair(seq):
    """
    Input: a sequence type, with the method random_get
    Output: a list containing a pair of randomly chosen items
    that are not identical
    """
    rv = []
    rv.append(seq.random_get())
    rv.append(seq.random_get())
    i = 0
    while rv[1].song_id == rv[0].song_id or rv[0].score == rv[1].score:
        rv[1] = seq.random_get()
        if i > 500:
            break 
        i += 1
    return rv[0], rv[1]
    

class BRSequenceIterator:
    """
    An iterator class which walks down the length
    of a BiasedRandomSequence, returning items in
    the order they were added
    """

    def __init__(self, sequence):
        self._seq = sequence
        self._current_index = 0

    def __next__(self):
        try:
            rv = self._seq[self._current_index]
        except IndexError:
            raise StopIteration
        
        self._current_index += 1
        
        return rv
