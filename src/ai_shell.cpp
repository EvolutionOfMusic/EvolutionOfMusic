/*
 * ai_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "ai_shell.h"

bool sig_flag = false;

Song ai_shell(bool continuing, bool displayText, int * iteration, int score) {
	static int last_song_id = -1;
	Song song;
	char buffer[100];

	// Init
	if (continuing && last_song_id == -1 && score == 0) {
		// Generation of songs is already done
	} else if (last_song_id == -1 && score == 0) {
		//Normal Initialization
		if (displayText)
			printf("ITERATION 0\n");
		// Prepare the signal handler
		init_AI();
		
		sprintf(buffer, 
			"python3 GA_Code/main.py -n -p %d -s %d", 
			getpid(), rand());
		system(buffer);
	       	//printf("PAUSING\n");
		// Wait for python's init to complete
		if (!sig_flag)
		    pause();
		sig_flag = false;
		
		
		//printf("THE WAIT IS OVER!\n");
	}

	// Pass the song & score to the AI
	//printf("AI INPUT\n");
	ofstream file("main_py_input", std::ios_base::app);
	if (file.is_open() && last_song_id != -1) {
		file << score << "\n";
		file.close();
	}
	song = start_AI(continuing, displayText, iteration);

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

Song start_AI(bool displayText, int * iteration) {
	static std::vector<Song> song_list;
	static int song_index = -1;
	//printf("START AI\n");
	if (song_index == -1){
	    // READ OUTPUT
	    ifstream file("./main_py_output");
	    song_list = parse_song(file);
	}
	
	if (song_index == song_list.size()-1) {
	        if (song_index != -1) set_sd(song_list);
		char buffer[100];
		
		if (displayText)
			printf("ITERATION %d\n", (*iteration)+1);

		// DO YOUR STUFF
		sprintf(buffer, "python3 GA_Code/main.py -p %d", getpid());
		system(buffer);
		
		// WAIT FOR OUTPUT (A SIGNAL FROM PYTHON'S KILL())
		if (!sig_flag)
		    pause();
		sig_flag = false;
		
		// READ OUTPUT
		ifstream file("./main_py_output");
		song_list = parse_song(file);
		
		// Index Change
		song_index = 0;
		//New Iteration
		(*iteration)++;
	} else {
		song_index++;
	}
	//printf("END AI\n");
	return song_list.at(song_index);
}

void sig_handler(int sig) {
	// We have resumed.
	// Re-init signal handler
	signal(SIGCONT, sig_handler);
	sig_flag = true;
	return;
}
