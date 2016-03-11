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
	        printf("SUPERVISOR START\n");
	        printf("Song track 0 length in Supervisor = %hd\n", song.tunes[0].track_length);
		score = supervisor(song);
	} else {
		score = manual_override(song);
	}
	  printf("SUPERVISOR END\n");
	return score;
}

int supervisor(Song song) {
	//JUDGE IT
	int score = 100;
	int tally = 0;

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
	int instruments = song.track_num, 
	    beat;
	float freq_ratio;
	Note a1, a2, a3, a4;

	printf("OMP START\n");
	printf("track_num is %d\n", instruments);
	// Parallelize on i, evaluates for errors within each track
        //#pragma omp parallel for num_threads(4) collapse(2) private(i, k, a1, a2, a3) reduction(+:tally)
	for (int i = 0;i < instruments;i++) {
		printf("JON's STUFF\n");
	        beat = 0;
		for (int k = 0;k < song.tunes[i].track_length;k++) {
		        if(score <= tally) continue;
			if(k == 0) {
				a1 = song.tunes[i].channel[0];
				a2 = song.tunes[i].channel[0];
				a3 = song.tunes[i].channel[0];
	    		} else if(k == 1) {
				a1 = song.tunes[i].channel[0];
				a2 = song.tunes[i].channel[0];
				a3 = song.tunes[i].channel[1];
			} else {
				a1 = song.tunes[i].channel[k-2];
				a2 = song.tunes[i].channel[k-1];
				a3 = song.tunes[i].channel[k];
			}
			printf("tally %d\n", tally);
			if((a3.tone == 0) && (a2.tone == 0))
				tally += 10;

	    		// Must be within an octave of the past two notes, not counting rests
	    		if(	((abs(a3.tone - a2.tone) >= 8) && (a2.tone != 0)) || 
	    			((abs(a3.tone - a1.tone) >= 8) && (a2.tone != 0))  )
				tally += 2;
			
			printf("STEPHEN's STUFF\n");
			if (a3.tone == 0) continue;
			for (int j = 0;j < instruments;j++) {
			    if (j == i) continue;
			    for (int l = 0;l < a3.hold_time; l++) {
			        if(score <= tally) continue;
				//printf("GET NOTE AT BEAT\n");
				a4 = getNoteAtBeat(song.tunes[j], beat+l);
				//printf("NOTE BEATING COMPLETE\n");
				if (a4.tone == -1 || a4.tone == 0) continue;// This channel has already ended
				printf("FREQ_RATIO for %d and %d\n", a3.tone, a4.tone);
				printf("FREQS are %d and %d\n", frequencies[a3.tone], frequencies[a4.tone]);
				if (frequencies[a3.tone] > frequencies[a4.tone]) {
				  freq_ratio = floor((100*frequencies[a3.tone]) / frequencies[a4.tone]);
				} else {
				  freq_ratio = floor((100*frequencies[a4.tone]) / frequencies[a3.tone]);
				}
				printf("FREQ_RATIO DONE\n");
				// If there is dissonance, -2 points
				if (!(	freq_ratio == 200 || // 2:1
					freq_ratio == 150 || // 3:2
					freq_ratio == 133 || // 4:3
					freq_ratio == 100))  // 1:1
				  tally += 2;
			    }
			}
			beat += a3.hold_time;
		}
	}
	printf("OMP END\n");
	score -= tally;
	printf("Score should be : %d / tally is %d\n", score, tally);
	if(score <= 0) return 0;
	return score;
}

Note getNoteAtBeat(Track track, int beat) {
        int o = -1, temp_beat = 0;
       	while (temp_beat < beat && o < track.track_length) {
       	    o++;
	    temp_beat += track.channel[o].hold_time;
       	}
	if (o == track.track_length) {Note n;n.tone = -1;return n;} 
	return track.channel[o];
}

int manual_override(Song song) {
	//JUDGE IT
	int score = 0;

	//UI Interactions
	//TODO

	return score;
}
