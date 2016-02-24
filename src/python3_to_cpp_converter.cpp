/* 
 * File:   python3_to_cpp_converter.cpp
 * Author: Lee Ingram, Stephen Andersen
 *
 * Created on February 8, 2016, 10:20 AM
 */

#include "python3_to_cpp_converter.h"

using namespace std;

Song parse_song(ifstream &file){
    char file_line[20];
	
	Song song;
	int NUM_TRACKS, NUM_NOTES, i, j,
		instr_id, volume;
	long int pause_time, hold_time, tone;
	
	if (file.is_open()) {
		// Number of Tracks
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &NUM_TRACKS);
		
		// Tempo
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &song.tempo);
		
		// SongID
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &song.song_id);
		
		for (i = 0;i < NUM_TRACKS;i++) {
			// Number of Notes
			file.getline(file_line, 20);
			sscanf(file_line, "%d", &NUM_NOTES);
		
			// Instrument ID, Volume
			file.getline(file_line, 20);
			sscanf(file_line, "%d %d", &instr_id, &volume);
			song.tunes[i].instrument_id = instr_id;
			song.tunes[i].volume = volume;
			
			for (j = 0;j < NUM_NOTES;j++) {
				// Pause Time, Tone, Hold Time
				file.getline(file_line, 20);
				sscanf(file_line, "%d %d %d", &pause_time, &tone, &hold_time);
				song.tunes[i].channel[j].tone = tone;
				song.tunes[i].channel[j].pause_time = pause_time;
				song.tunes[i].channel[j].hold_time = hold_time;
			}
		}
	}
	
	return song;
}

int main(int argc, char** argv) {
    Song song;
    char songid[5];
    
    ifstream file("main_py_output");
    
    song = parse_song(file);
	
	Track track = song.tunes[0];
    
    cout << track.instrument_id << endl;
    cout << track.volume << endl;
}

