/*
 * ai_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "ai_shell.h"

Song ai_shell(int score) {
	static Song song = null;

	// Init
	if (song == null &&
		score == 0) {
		sprintf(buffer, 25, "python3 main.py -n %d", rand())
		system(buffer);
	}

	// Pass the song & score to the AI
	song = start_AI(score);

	return song;
}

Song start_AI(int score) {
	Song song;
	char * buffer;

	// DO YOUR STUFF
	sprintf(buffer, 25, "python3 main.py -g", rand());
	system(buffer);
	
	return song;
}
