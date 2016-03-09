/*
 * ai_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "ai_shell.h"

bool sig_flag = false;

Song ai_shell(int * iteration, int score) {
	static int last_song_id = -1;
	Song song;
	char buffer[100];

	// Init
	if (last_song_id == -1 &&
		score == 0) {
		// Prepare the signal handler
		init_AI();
		
		sprintf(buffer, 
			"python3 GA_Code/main.py -n -p %d -s %d", 
			getpid(), rand());
		system(buffer);
	       	printf("PAUSING\n");
		// Wait for python's init to complete
		if (!sig_flag)
		    pause();
		sig_flag = false;
		
		
		printf("THE WAIT IS OVER!\n");
	}

	// Pass the song & score to the AI
	printf("AI INPUT\n");
	ofstream file("main_py_input", std::ios_base::app);
	if (file.is_open() && last_song_id != -1) {
		file << score << "\n";
		file.close();
	}
	song = start_AI(iteration);

	last_song_id = song.song_id;
	
	return song;
}

void init_AI() {
	// Init signal handler for first use
	sig_handler(0);
	
	// Clear the file
	ofstream file("main_py_input", std::ofstream::out | std::ofstream::trunc);
	if (file.is_open())	file.close();
}

Song start_AI(int * iteration) {
	static std::vector<Song> song_list;
	static int song_index = -1;
	printf("START AI\n");
	if (song_index == -1){
	    // READ OUTPUT
	    ifstream file("./GA_Code/main_py_output");
	    song_list = parse_song(file);
	    song_index++;
	}
	
	if (song_index == song_list.size()-1) {
	        if (song_index != -1) set_sd(song_list);
		char buffer[100];

		// DO YOUR STUFF
		sprintf(buffer, "python3 GA_Code/main.py -p %d", getpid());
		system(buffer);
		
		// WAIT FOR OUTPUT (A SIGNAL FROM PYTHON'S KILL())
		if (!sig_flag)
		    pause();
		sig_flag = false;
		
		// READ OUTPUT
		ifstream file("./GA_Code/main_py_output");
		song_list = parse_song(file);
		
		// Index Change
		song_index = 0;
		//New Iteration
		(*iteration)++;
	} else {
		song_index++;
	}
	printf("END AI\n");
	printf("Song track_num in AI = %hd\n", 
	       song_list.at(song_index).track_num);
	printf("Track_length Before Leaving AI for Song %hd = %hu\n", 
	       song_list.at(song_index).song_id, 
	       song_list.at(song_index).tunes[0].track_length);
	printf("TO ENSURE THAT TRACKS ARE DIFFERENT\n");
	printf("TRACK 0, 1st Note: %d\n", 
	       song_list.at(song_index).tunes[0].channel[0].tone);	
	printf("TRACK 1, 1st Note: %d\n", 
	       song_list.at(song_index).tunes[0].channel[1].tone);
	return song_list.at(song_index);
}

void sig_handler(int sig) {
	// We have resumed.
	// Re-init signal handler
	signal(SIGCONT, sig_handler);
	sig_flag = true;
	return;
}
