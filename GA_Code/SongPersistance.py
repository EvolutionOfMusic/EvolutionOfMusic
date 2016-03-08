from NoteGene import NoteGene
from NoteChromosome import NoteChromosome
from GeneticSong import GeneticSong


def save_songs(save_file, *songs, delimeter='*'):
    with open("genetic_" + save_file, 'w+') as sav_file:
        song_string = ''
        for song in songs:
            song_string += (song.__repr__() + '\n{}\n'.format(delimeter))

        song_string = song_string.strip('\n{}\n'.format(delimeter))
        sav_file.write(song_string)

def gene_from_string(gene_string, config_file):
    """
    >>> gene1 = NoteGene(1,2,3,2,1)
    >>> gene1
    [1, 2, 3, 2, 1]
    >>> gene2 = gene_from_string("[1, 2, 3, 2, 1]")
    >>> gene1 == gene2
    True
    """
    param_list = gene_string.replace('[', '').replace(']', '').split(',')
    param_list = map(int, param_list)

    t_range = range(config_file.min_note, config_file.max_note + 1)
    h_range = range(config_file.min_hold_time, config_file.max_hold_time + 1)
    
    return NoteGene(*param_list, max_pause=config_file.max_pause_time, tone_range=t_range,
                    hold_range=h_range, safe_mutation=True)

def chromosome_from_string(chromo_string, config_file):
    """
    >>> gene1 = NoteGene(1,1,1,1,1)
    >>> gene2 = NoteGene(2,2,2,2,2)
    >>> nc1 = NoteChromosome(gene1, gene2, track_id=0, volume=1)
    >>> nc2 = chromosome_from_string("0\\n1\\n[1, 1, 1, 1, 1]\\n[2, 2, 2, 2, 2]")
    >>> nc1 == nc2
    True
    """
    track_id, volume = map(int, chromo_string.split('\n')[:2])
    
    param_list = chromo_string.split('\n')[2:]
    gene_list = []
    for param in param_list:
        gene_list.append(gene_from_string(param, config_file))
    return NoteChromosome(*gene_list, track_id=track_id, volume=volume)

def song_from_string(song_string, config_file):
    """
    >>> gene1 = NoteGene(1,1,1,1,1)
    >>> gene2 = NoteGene(2,2,2,2,2)
    >>> gene3 = NoteGene(3,3,3,3,3)
    >>> gene4 = NoteGene(4,4,4,4,4)
    >>> nc1 = NoteChromosome(gene1,gene2,track_id=0,volume=1)
    >>> nc2 = NoteChromosome(gene3,gene4,track_id=2,volume=3)
    >>> song1 = GeneticSong(nc1, nc2)
    >>> song2 = song_from_string(song1.__repr__())
    >>> song1 == song2
    True
    """
    meta_data_list = song_string.split('\n')[0:2]  
    song_id, tempo = map(int, meta_data_list)
    chromo_strings = song_string.split('\n', 2)[-1].replace('\n\n', '*').split('*')

    chromo_list = [chromosome_from_string(string, config_file) for string in chromo_strings]

    rv = GeneticSong(*chromo_list)
    rv.song_id = song_id
    rv.tempo = tempo
    
    return rv

def load_songs(load_file, config_file, delimeter='*'):
    with open("genetic_" + load_file) as file_obj:
        rv = []
        file_contents = file_obj.read().split('\n{}\n'.format(delimeter))

        for song_string in file_contents:
            rv.append(song_from_string(song_string, config_file))
        return rv
