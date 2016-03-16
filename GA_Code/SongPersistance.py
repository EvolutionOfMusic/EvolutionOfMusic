from NoteGene import NoteGene
from NoteChromosome import NoteChromosome
from GeneticSong import GeneticSong


def save_songs(save_file, *songs, delimeter='*'):
    with open(save_file + "_genetic", 'w+') as sav_file:
        song_string = ''
        for song in songs:
            song_string += (song.__repr__() + '\n{}\n'.format(delimeter))

        song_string = song_string.strip('\n{}\n'.format(delimeter))
        sav_file.write(song_string)

def gene_from_string(gene_string, config_file):
    param_list = gene_string.replace('[', '').replace(']', '').split(',')
    param_list = map(int, param_list)

    t_range = range(config_file.min_note, config_file.max_note + 1)
    h_range = range(config_file.min_hold_time, config_file.max_hold_time + 1)
    
    return NoteGene(*param_list, max_pause=config_file.max_pause_time, tone_range=t_range,
                    hold_range=h_range, safe_mutation=True)

def chromosome_from_string(chromo_string, config_file):
    track_id, volume = map(int, chromo_string.split('\n')[:2])
    
    param_list = chromo_string.split('\n')[2:]
    gene_list = []
    for param in param_list:
        gene_list.append(gene_from_string(param, config_file))
    return NoteChromosome(*gene_list, track_id=track_id, volume=volume)

def song_from_string(song_string, config_file):
    meta_data_list = song_string.split('\n')[0:2]  
    song_id, tempo = map(int, meta_data_list)
    chromo_strings = song_string.split('\n', 2)[-1].replace('\n\n', '*').split('*')

    chromo_list = [chromosome_from_string(string, config_file) for string in chromo_strings]
    t_range = range(config_file.min_tempo, config_file.max_tempo + 1)
    rv = GeneticSong(*chromo_list, tempo=tempo, tempo_range=t_range)
    rv.song_id = song_id
    
    return rv

def load_songs(load_file, config_file, delimeter='*'):
    with open(load_file + "_genetic", 'r') as file_obj:
        rv = []
        file_contents = file_obj.read().split('\n{}\n'.format(delimeter))

        for song_string in file_contents:
            rv.append(song_from_string(song_string, config_file))
        return rv
