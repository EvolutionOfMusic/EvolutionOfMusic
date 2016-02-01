/*
 * critic_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "critic_shell.h"

int c_shell(Song song) {
	int score = 100;

	if (override_switch()) {
		score = supervisor(song);
	} else {
		score = manual_override(song);
	}

	return score;
}

int supervisor(Song song) {
	//JUDGE IT
	int score = 0;

	// A Song holds Tracks; A Track holds Notes
	//TODO

	return score;
}

int manual_override(Song song) {
	//JUDGE IT
	int score = 0;

	//UI Interactions
	//TODO

	return score;
}

bool override_switch() {
	//TODO
	return true;
}
