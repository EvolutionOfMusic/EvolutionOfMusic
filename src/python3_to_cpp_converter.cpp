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
	
	short int NUM_SONGS, NUM_TRACKS, NUM_NOTES;
	printf("start song list\n");
	if (file.is_open()) {
		// Number of Songs
		file.getline(file_line, 20);
		sscanf(file_line, "%hd", &NUM_SONGS);
		
		for (int i = 0;i < NUM_SONGS;i++) {
			// Make a new song
			Song song;
			
			// Number of Tracks
			file.getline(file_line, 20);
			sscanf(file_line, "%hd", &NUM_TRACKS);
			song.track_num = NUM_TRACKS;
			
			// Tempo
			file.getline(file_line, 20);
			sscanf(file_line, "%hd", &song.tempo);
			
			// SongID
			file.getline(file_line, 20);
			sscanf(file_line, "%d", &song.song_id);
			
			for (int j = 0;j < NUM_TRACKS;j++) {
				// Number of Notes
				file.getline(file_line, 20);
				sscanf(file_line, "%hd", 
				       &NUM_NOTES);
				song.tunes[j].track_length = NUM_NOTES;
				
				// Instrument ID, Volume
				file.getline(file_line, 20);
				sscanf(file_line, "%hd %hd", 
				       &(song.tunes[j].instrument_id), 
				       &(song.tunes[j].volume));
				
				for (int k = 0;k < NUM_NOTES;k++) {
					// Pause Time, Tone, Hold Time
					short int a, b, c;
					file.getline(file_line, 20);
					sscanf(file_line, "%hd %hd %hd", &a, &b, &c);
					song.tunes[j].channel[k].pause_time = a; 
					song.tunes[j].channel[k].tone = b;
					song.tunes[j].channel[k].hold_time = c;
				}
			}
			// Add it to the list
			song_list.push_back(song);
		}
	}
	printf("finished song_list\n");
	return song_list;
}

