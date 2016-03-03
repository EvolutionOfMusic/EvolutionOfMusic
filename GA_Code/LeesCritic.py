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

INPUT_FILE = "genetic_main_py_output"
OUTPUT_FILE = "main_py_input"
PERFECT_SCORE = 20

if __name__ == "__main__":
    with open(INPUT_FILE) as song_file:
        file_text = song_file.read()
        
    song_list = parse_songs(file_text)
    grades = [grade_song(song, PERFECT_SCORE) for song in song_list]
    total_score = sum(grades)
    average = total_score/len(grades)

    with open(OUTPUT_FILE, 'w') as grade_file:
        for grade in grades:
            grade_file.write(str(grade) + '\n')

    print("Average fitness is: {}".format(average))
    print("Max fitness is: {}".format(max(grades)))
