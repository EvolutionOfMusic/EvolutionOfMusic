from random import randrange


def parse_songs(string):
    string_list = map(remove_meta_data, string.split('*'))
    return list(map(get_song, string_list))

def remove_meta_data(string):
    return string.strip('\n').split('\n',4)[-1]

def get_tone(string):
    return int(string.strip('[]').split(',')[2])

def get_song(string):
    return list(map(get_tone, string.strip('\n').split('\n')))

def abs(num):
    if num < 0:
        num *= -1
    return num

def avg(*vals):
    return sum(vals)/len(vals)

def count_songs(string):
    return len(string.split('*'))
    

def grade_song(song, perfect_score):
    ideal_note = 1
    deduction = 0
    for tone in song:
        deduction += abs(ideal_note - tone)
        ideal_note += 1
    score = perfect_score - deduction
    if score < 0:
        score = 0
    return score



def get_diversity(song1, song2):
    if len(song1) > len(song2):
        song2 += ([0]*(len(song1) - len(song2)))
    if len(song2) > len(song1):
        song1 += ([0]*(len(song1) - len(song2)))
    return avg(*[abs(song1[i] - song2[i]) for i in range(len(song2))])
    

class DiversityCalc:

    def __init__(self, val):
        self.song = val

    def __call__(self, val):
        return get_diversity(self.song, val)

INPUT_FILE = "genetic_main_py_output"
OUTPUT_FILE = "main_py_input"
PERFECT_SCORE = 20

if __name__ == "__main__":
    with open(INPUT_FILE) as song_file:
        file_text = song_file.read()
        
    with open(INPUT_FILE) as input_file:
        file_string = input_file.read()
        song_count = len(file_string)
        
    grades = [randrange(1, 100) for i in range(song_count)]
    
    with open(OUTPUT_FILE, 'w') as grade_file:
        for grade in grades:
            grade_file.write(str(grade) + '\n')
