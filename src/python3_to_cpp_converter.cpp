/* 
 * File:   python3_to_cpp_converter.cpp
 * Author: Lee Ingram, Stephen Andersen
 *
 * Created on February 8, 2016, 10:20 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include "song_structs.h"

using namespace std;

Song parse_song(ifstream &file){
    /*char file_line[20];
    char flow_control; 
    static int i = 0, j = 0;   
    status function_status;
    long int pause_time, hold_time, tone;
    
    if(file.is_open()){ 
        while(1) { 
            file.getline(file_line, 20);
            
            flow_control = file_line[0];
            if(flow_control == '%'){
                function_status = EOT;
                break;
            }
            
            if(flow_control == '*'){
                function_status = EOS;
                break;
            }
            cout << "line 43" << endl;
            if(flow_control == '#'){
                function_status = EOSF;
                break;
            }
            
            if(i == 0){
                track_ptr.instrument_id = atol(file_line);
            } else if (i == 1) {
                track_ptr.volume = atol(file_line);
            } else {
                sscanf(file_line, "%d %d %d", &pause_time, &tone, &hold_time);
                track_ptr.channel[j].hold_time = hold_time;
                track_ptr.channel[j].pause_time = pause_time;
                track_ptr.channel[j].tone = tone;
                j++;
            } 
            
            i++;
            
        } 
    }
    
    i = 0;
    j = 0;
    
    return function_status;*/
	char file_line[20];
	
	Song song;
	int NUM_TRACKS,
		instr_id, volume;
	long int pause_time, hold_time, tone;
	
	if (file.is_open()) {
		// SongID
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &song.song_id);
		
		// Number of Tracks
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &NUM_TRACKS);
		
		for (i = 0;i < NUM_TRACKS;i++) {
			// Instrument ID, Volume
			file.getline(file_line, 20);
			sscanf(file_line, "%d %d", &instr_id, &volume);
			song.tunes[i].instrument_id = instr_id;
			song.tunes[i].volume = volume;
			
			for (j = 0;j < MAX_NOTES;j++) {
				// Pause Time, Tone, Hold Time
				file.getline(file_line, 20);
				sscanf(file_line, "%d %d %d", &pause_time, &tone, &hold_time);
				song.track[i].tone = tone;
				song.track[i].pause_time = pause_time;
				song.track[i].hold_time = hold_time;
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
	
	Track track = song.track[0];
    
    cout << track.instrument_id << endl;
    cout << track.volume << endl;
}

