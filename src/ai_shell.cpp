/*
 * ai_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "ai_shell.h"

Song ai_shell(int score) {
	static Song song;

	// Pass the song & score to the AI
	song = start_AI(score);

	return song;
}

Song start_AI(int score) {
	Song song;

	// DO YOUR STUFF
	// rand();

	return song;
}
