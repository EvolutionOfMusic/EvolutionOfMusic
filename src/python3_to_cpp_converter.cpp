/* 
 * File:   python3_to_cpp_converter.cpp
 * Author: Lee Ingram, Stephen Andersen
 *
 * Created on February 8, 2016, 10:20 AM
 */

#include "python3_to_cpp_converter.h"

using namespace std;

std::vector<Song> parse_song(ifstream &file){
    char file_line[20];
	
	std::vector<Song> song_list;
	
	int NUM_SONGS, NUM_TRACKS, NUM_NOTES;
	
	if (file.is_open()) {
		// Number of Songs
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &NUM_SONGS);
		
		for (int i = 0;i < NUM_SONGS;i++) {
			// Make a new song
			Song song;
			
			// Number of Tracks
			file.getline(file_line, 20);
			sscanf(file_line, "%d", &NUM_TRACKS);
			
			// Tempo
			file.getline(file_line, 20);
			sscanf(file_line, "%d", &song.tempo);
			
			// SongID
			file.getline(file_line, 20);
			sscanf(file_line, "%d", &song.song_id);
			
			for (int j = 0;j < NUM_TRACKS;j++) {
				// Number of Notes
				file.getline(file_line, 20);
				sscanf(file_line, "%d", &NUM_NOTES);
			
				// Instrument ID, Volume
				file.getline(file_line, 20);
				sscanf(file_line, "%d %d", 
					&song.tunes[j].instrument_id, 
					&song.tunes[j].volume);
				
				for (int k = 0;k < NUM_NOTES;k++) {
					// Pause Time, Tone, Hold Time
					file.getline(file_line, 20);
					sscanf(file_line, "%d %d %d", 
						&song.tunes[j].channel[k].pause_time, 
						&song.tunes[j].channel[k].tone, 
						&song.tunes[j].channel[k].hold_time)
				}
			}
			// Add it to the list
			song_list.push_back(song);
		}
	}
	
	return song_list;
}

