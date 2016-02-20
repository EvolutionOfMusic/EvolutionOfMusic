from random import SystemRandom


class BiasedRandomSequence:
    """
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
        self._data_dict = dict()
        self._index_to_range_dict = dict()
        self._max_prob_index = 0
        self._randomizer = SystemRandom()

        if insert_key is not None:
            for item in new_items:
                self.append(insert_key(item), item)
            

    @property
    def max_index(self):
        return len(self) - 1

    def __len__(self):
        return len(self._data_dict)

    
    def __repr__(self):
        """
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
        return BRSequenceIterator(self)

    def _prob_to_range(self, prob):
        return range(self._max_prob_index, prob + self._max_prob_index)
    
    def append(self, prob, value):
        self._data_dict[self._prob_to_range(prob)] = value
        self._index_to_range_dict[self.max_index] = self._prob_to_range(prob)
        self._max_prob_index += prob
        
    def random_get(self):
        prob_index = self._randomizer.randrange(self._max_prob_index)
        for key in self._data_dict.keys():
            if prob_index in key:
                return self._data_dict[key]

def sample_pair(seq):
    rv = []
    rv.append(seq.random_get())
    rv.append(seq.random_get())

    while rv[1] == rv[0]:
        rv[1] = seq.random_get()

    return rv
    

class BRSequenceIterator:

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
