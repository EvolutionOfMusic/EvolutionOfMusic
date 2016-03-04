/*
 * ai_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "ai_shell.h"

Song ai_shell(int score) {
	static Song song.song_id = -1;
	char * buffer;

	// Init
	if (song.song_id == -1 &&
		score == 0) {
		// Prepare the signal handler
		init_AI();
		
		sprintf(buffer, "python3 main.py -n -p %d -s %d", getpid(), rand());
		system(buffer);
		
		// Wait for python's init to complete
		pause();
	}

	// Pass the song & score to the AI
	song = start_AI(score);

	return song;
}

void init_AI() {
	// Init signal handler for first use
	sig_handler(0);
	
	// Clear the file
	ofstream file("main_py_input", std::ofstream::out | std::ofstream::trunc);
	if (file.is_open())	file.close();
}

Song start_AI(int score) {
	static std::vector<Song> song_list;
	static int song_index = -1;
	
	ofstream file("main_py_input", std::ios_base::app);
	if (file.is_open()) {
		file << score << "\n";
		file.close();
	}
	
	if (song_index == song_list.size() ||
		song_index == -1) {
		if (song_index != -1) set_sd(song_list);
		char * buffer;

		// DO YOUR STUFF
		sprintf(buffer, "python3 main.py");
		system(buffer);
		
		// WAIT FOR OUTPUT (A SIGNAL FROM PYTHON'S KILL())
		pause();
		
		// READ OUTPUT
		ifstream file("main_py_output");
		song_list = parse_song(file);
		
		// Index Change
		song_index = 0;
	} else {
		song_index++;
	}
	
	return song_list.at(song_index);
}

void sig_handler(int sig) {
	// We have resumed.
	// Re-init signal handler
	signal(SIGCONT, sig_handler);
	return;
}
