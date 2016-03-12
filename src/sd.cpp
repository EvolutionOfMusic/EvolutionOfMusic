/*
 * sd.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: Stephen
 */


#include "sd.h"

const int port_number = 1111;

void error(const char *msg){
	perror(msg);
}

void init_sd() {
	ofstream toSD;
	toSD.open("music", std::ofstream::out | std::ofstream::trunc);
	if (toSD.is_open()) toSD.close();
}

void set_sd(std::vector<Song> song_list) {
	ofstream toSD;
	toSD.open("music");
	if (toSD.is_open()) {
		// NUM_SONGS
		toSD << song_list.size() << "\n";
		for(std::vector<Song>::iterator it = song_list.begin();
			it != song_list.end();
			it++) {
			int NUM_TRACKS = (*it).track_num;//sizeof((*it).tunes)/sizeof(Track);
			//NUM_TRACKS
			toSD << NUM_TRACKS << "\n";
			//TEMPO
			toSD << (*it).tempo << "\n";
			//SONG_ID
			toSD << (*it).song_id << "\n";
			
			for (int i = 0;i < NUM_TRACKS;i++) {
				int NUM_NOTES = (*it)tunes[i].track_length;//sizeof((*it).tunes[i])/sizeof(Note);
				//NUM_NOTES
				toSD << NUM_NOTES << "\n";
				//INSTRUMENT_ID, VOLUME
				toSD << (*it).tunes[i].instrument_id << " " << (*it).tunes[i].volume << "\n";;
				
				for (int j = 0;j < NUM_NOTES;j++) {
					//PAUSE_TIME, TONE, HOLD_TIME
					toSD << (*it).tunes[i].channel[j].pause_time << " " << 
						(*it).tunes[i].channel[j].tone << " " << 
						(*it).tunes[i].channel[j].hold_time << "\n";
				}
			}
		}
		toSD << "\n";
		toSD.close();
	}
}
