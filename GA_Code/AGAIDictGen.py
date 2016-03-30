import json
import itertools

from ConfigFile import ConfigFile

def gen_tone_list(con_file):
    return [i for i in range(con_file.min_note, con_file.max_note + 1)]

def gen_note_list(con_file):
    return [(i, j, k) 
            for i in range(con_file.max_pause + 1)
            for j in range(con_file.min_note, con_file.max_note + 1)
            for k in range(con_file.min_hold_time, con_file.max_hold_time + 1)]

def get_pairs(arg):
    return itertools.product(arg, arg)

def init_score_dict(*args):
    return {arg: 1 for arg in args}

def init_song_indexs(arg, con_file):
    return {i:arg for i in range(con_file.chromo_length)}

def save_to_file(arg, file_name):
    with open(file_name, 'w+') as out_file:
        out_file.write(json.dumps(arg))

def init_ega_dict(con_file, *args):
    rv = get_pairs(args)
    rv = init_score_dict(*args)
    rv = init_song_indexs(args, con_file)
    
def get_con_dict(con_file):
    t_list = get_tone_list(con_file)
    wv = init_ega_dict(con_file, *t_list)
    save_to_file(wv, "con_dict_file")

def get_note_dict(con_file):
    n_list = get_note_list(con_file)
    wv = init_ega_dict(con_file, *t_list)
    save_to_file(wv, "tone_list_file")
    
