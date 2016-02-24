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
		score == 0)
		system(sprintf(buffer, 25, "python3 main.py -n %d", rand()));

	// Pass the song & score to the AI
	song = start_AI(score);

	return song;
}

Song start_AI(int score) {
	Song song;
	char * buffer;

	// DO YOUR STUFF
	system(sprintf(buffer, 25, "python3 main.py -g", rand()));

	return song;
}
