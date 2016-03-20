from threading import Thread
import json 

def list_subtract(list1, list2):
    """
    Input: a list l1 of lenth x, and a list l2 of length y
    Output: if x > y or y > x, the elements from the indicies in one list
    that do not overlap the indicies of anotherthe indices in l2, 
    else an empty list
    
    >>> list_subtract([1, 2], [3, 4, 5])
    [5]
    >>> list_subtract([3, 4, 5], [1, 2])
    [5]
    >>> list_subtract([1, 2], [3, 4])
    []
    """
    l1 = max(list1, list2, key=len)
    l2 = min(list1, list2, key=len)
    return l1[len(l2):] 

abs_sub = lambda a, b: abs(a - b) 

def get_diversity(list1, list2):
    """
    Input: list1, list2
    Output: the numerical difference between the lists

    >>> get_diversity([1, 1, 1], [1, 1, 1])
    0
    >>> get_diversity([1, 1, 1], [3, 3, 3])
    6
    >>> get_diversity([3, 3, 3], [1, 1, 1])
    6
    >>> get_diversity([1, 1, 1], [1, 1])
    1
    >>> get_diversity([1, 1], [1, 1, 1])
    1
    """
    list_a = map(abs_sub, list1, list2)
    list_b = list_subtract(list1, list2)
    return sum(list_a) + sum(list_b) 

def get_avg_diversity(list1, *lists):
    """
    Input: a list and a list of lists
    Output: the average diversity of list1, with respect to the other lists

    >>> get_avg_diversity([1, 2, 3], [1, 2], [3, 4], [1, 2, 3], [1, 2, 3, 4])
    3.5
    """ 
    rv = 0
    for l in lists:
        rv += get_diversity(list1, l)
    return rv/len(lists)

def save_as_flat_dict(song_list, config_file): 
    flat_dict = {song.song_id:song.flatten() for song in song_list}
    with open(config_file.output_file + "_flat", 'w+') as json_file:
        json_file.write(json.dumps(flat_dict))

def create_diversity_dict(out_file, *song_list):
    flat_dict = {song.song_id:song.flatten() for song in song_list}
    diversity_dict = {song.song_id:get_avg_diversity(flat_dict[song.song_id], *flat_dict.items()) 
                      for song in song_list}
    with open(out_file, 'w+') as json_file:
        json_file.write(json.dumps(diversity_dict))
    

    
    
