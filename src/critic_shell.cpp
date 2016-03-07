/*
 * critic_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "critic_shell.h"

int c_shell(Song song) {
	int score = 100;

	if (true) {
		score = supervisor(song);
	} else {
		score = manual_override(song);
	}

	return score;
}

int supervisor(Song song) {
	//JUDGE IT
	int score = 100;
	int tally = 0;
	int i, j, k;

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
	Note a1, a2, a3, n1, n2;

	// Parallelize on i, evaluates for errors within each track
	#pragma omp parallel for num_threads(4) collapse(2) private(i, k)
	for (i = 0;i < instruments;i++) {
		for (k = 0;k < track_length;k++) {
	    		//if(score <= 0) break; // DNW
	    		if(i == 0) {
				a1 = song.tunes[i].channel[0];
				a2 = song.tunes[i].channel[0];
				a3 = song.tunes[i].channel[0];
	    		} else if(i == 1) {
				a1 = song.tunes[i].channel[0];
				a2 = song.tunes[i].channel[0];
				a3 = song.tunes[i].channel[1];
			} else {
				a1 = song.tunes[i].channel[k-2];
				a2 = song.tunes[i].channel[k-1];
				a3 = song.tunes[i].channel[k];
			}
			
			// TODO: FIX THIS ;Not allowing two rests in a row
			if((a3.tone == 0) && (a2.tone == 0))
				score -= 10;

	    		// Must be within an octave of the past two notes, not counting rests
	    		if(	((abs(a3.tone - a2.tone) >= 8) && (a2.tone != 0)) || 
	    			((abs(a3.tone - a1.tone) >= 8)&& (a2.tone != 0))  )
				score -= 2;
	    	    
		}
	}
	
	// Parallelize k; evaluates for dissonance between tracks
	#pragma omp parallel for num_threads(4) collapse(3) private(i, j, k) reduction(+:tally)
	for (k = 0;k < track_length;k++) {
		for (i = 0;i < instruments;i++) {
			for (j = 0;j < instruments;j++) {
				//if(score <= 0) break; // DNW
				
				n1 = song.tunes[i].channel[k]; // Pick One Moment in Time
				n2 = song.tunes[j].channel[k]; // Compare to Different Instrument
				
				if (frequencies[n1.tone] > frequencies[n2.tone]) {
					freq_ratio = floor((100*frequencies[n1.tone]) / frequencies[n2.tone]);
				} else {
					freq_ratio = floor((100*frequencies[n2.tone]) / frequencies[n1.tone]);
				}

				// If there is dissonance, -2 points
				if (!(	freq_ratio == 200 || // 2:1
					freq_ratio == 150 || // 3:2
					freq_ratio == 133 || // 4:3
					freq_ratio == 100))	 // 1:1
					tally += 2;
			}
		}
	}
	score -= tally;
	if(score <= 0) {
		return 0;
	}

	return score;
}

int manual_override(Song song) {
	//JUDGE IT
	int score = 0;

	//UI Interactions
	//TODO

	return score;
}
