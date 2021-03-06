/*
 * ai_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "ai_shell.h"

//bool sig_flag = false;

Song ai_shell(bool continuing, bool displayText, int * iteration, long long score) {
	static int last_song_id = -1;
	Song song;
	char buffer[100];
	
	if (last_song_id == -1 && score == 0) {
		//Normal Initialization
		if (displayText)
			printf("ITERATION 0\n");
		// Prepare the signal handler
		init_AI();
		
		if (!continuing) {
			sprintf(buffer, 
				"python3 GA_Code/main.py -n -s %d -p %d", 
				rand(), getpid());
			system(buffer);
		}
	}

	song = start_AI(displayText, iteration, score);
	last_song_id = song.song_id;
	
	return song;
}

int get_diversity(std::list<Song> song_list, std::list<Song>::iterator current) {
	Song song = (*current);//song_list.at(song_index);
	int diversity = 0;
	//# pragma omp parallel for num_threads(4) reduction(-:diversity)
	for(std::list<Song>::iterator it = song_list.begin();it != song_list.end();it++)
	    if ((*it).song_id != song.song_id)
	        for (int i = 0;i < song.track_num;i++)
	            for (int j = 0;j < (*it).tunes[i].track_length;j++)
	                if (j >= song.tunes[i].track_length) {
	                    diversity += 	(*it).tunes[i].channel[j].tone +
	                            (*it).tunes[i].channel[j].pause_time + 
	                            (*it).tunes[i].channel[j].hold_time;
	                } else {
	                    diversity += 	abs(song.tunes[i].channel[j].tone - (*it).tunes[i].channel[j].tone) +
	                            abs(song.tunes[i].channel[j].pause_time - (*it).tunes[i].channel[j].pause_time) +
	                            abs(song.tunes[i].channel[j].hold_time - (*it).tunes[i].channel[j].hold_time);
	                }
	return diversity/song_list.size();
}

void init_AI() {
	// Clear the file
	std::ofstream file("main_py_input", std::ofstream::out | std::ofstream::trunc);
	if (file.is_open()) file.close();
}

Song start_AI(bool displayText, int * iteration, long long score) {
	static std::list<Song> song_list;
	static std::list<Song>::iterator it;
	static int song_index = -1;
	
	if (song_index == -1){
		// READ OUTPUT
		std::ifstream file("./main_py_output");
		song_list = parse_song(file);
		it = song_list.begin();
		it--;
	} else {
		// Pass the song & score to the AI
		std::ofstream file("main_py_input", std::ios_base::app);
		if (file.is_open()) {
			file << score << " " << get_diversity(song_list, it) << "\n";
			file.close();
		}
	}
	
	if (song_index == song_list.size()-1) {
	    	char buffer[100];
		
		if (displayText)
			printf("ITERATION %d\n", (*iteration)+1);

		// DO YOUR STUFF
		sprintf(buffer, "python3 GA_Code/main.py -p %d", getpid());
		system(buffer);
		
		// READ OUTPUT
		std::ifstream file("./main_py_output");
		song_list = parse_song(file);
		it = song_list.begin();
		
		// Index Change
		song_index = 0;
		//New Iteration
		(*iteration)++;
	} else {
		song_index++;
		it++;
	}
	
	return (*it);//song_list.at(song_index);
}

