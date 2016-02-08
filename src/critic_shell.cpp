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
	int tally = MAX_NOTES;

	/* A Song holds Tracks; A Track holds Notes
	//TODO: Finish
	 * Consonance is good; Dissonance is bad
	 * https://en.wikipedia.org/wiki/Consonance_and_dissonance
	 * https://musicmasterworks.com/WhereMathMeetsMusic.html
	 * https://en.wikipedia.org/wiki/Pythagorean_tuning
	 * http://hyperphysics.phy-astr.gsu.edu/hbase/music/mussca.html
	 *
	 * Rhythm
	 *
	 *
	 * Length
	 *
	 */
	int instruments = sizeof(song.tunes)/sizeof(Track),
		track_length = sizeof(song.tunes[0].channel)/sizeof(Note),
		freq_ratio;
	Note n1, n2;

	// Inefficient; Could do better
	for (int i = 0;i < instruments;i++) {
		for (int j = 0;j < track_length;j++) {
			for (int k = 0;k < track_length;k++) {
				n1 = song.tunes[i].channel[j];
				n2 = song.tunes[i].channel[k];

				if (frequencies[n1.tone] > frequencies[n2.tone]) {
					freq_ratio = floor((100*frequencies[n1.tone]) / frequencies[n2.tone]);
				} else {
					freq_ratio = floor((100*frequencies[n2.tone]) / frequencies[n1.tone]);
				}

				// If there is dissonance, -1/MAX_NOTE points
				if (!(	freq_ratio == 200 || // 2:1
						freq_ratio == 150 || // 3:2
						freq_ratio == 133 || // 4:3
						freq_ratio == 100))	 // 1:1
					tally--;
			}
		}
	}

	return tally / MAX_NOTES;
}

int manual_override(Song song) {
	//JUDGE IT
	int score = 0;

	//UI Interactions
	//TODO

	return score;
}

bool override_switch() {
	info status = get_ethernet();
	return status.manual_override;
}
