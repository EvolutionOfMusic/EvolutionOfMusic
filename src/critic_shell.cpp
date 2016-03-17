/*
 * critic_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "critic_shell.h"

const int NOTES_PER_OCTAVE = 12;
const int BEATS_PER_MEASURE = 16;
const int C7_INDEX = 6 * NOTES_PER_OCTAVE + 1;

int c_shell(Song song) {
	int score = 100;

	if (true) {
	        printf("SUPERVISOR START\n");
	        //printf("Song track 0 length in Supervisor = %hd\n", song.tunes[0].track_length);
		score = supervisor(song);
	} else {
		score = manual_override(song);
	}
	  printf("SUPERVISOR END\n");
	return score;
}

int supervisor(Song song) {
	//JUDGE IT
	int score = 0;
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
	int resolution_diff;
	Note a1, a2, a3, a4, n1, n2, n3;
	
	// We want songs with more tracks
	if (instruments < 8) {
		tally += (8-instruments)*400;
	} else {
		tally -= (instruments-8)*100;
	}

	//printf("OMP START\n");
	// Parallelize on i, evaluates for errors within each track
        //#pragma omp parallel for num_threads(4) collapse(2) private(i, k, a1, a2, a3) reduction(+:tally)
	for (int i = 0;i < instruments;i++) {
		//printf("JON's STUFF\n");
	        beat = 0;
	        
	        n1 = song.tunes[i].channel[0];
		n2 = song.tunes[i].channel[song.tunes[i].track_length -2];
		n3 = song.tunes[i].channel[song.tunes[i].track_length -1];
	        
	        // Song is silent at the beginning...
			if (n1.tone == REST)
				tally += 10*song.tunes[i].track_length;
	        
	        // Track has poor ending, last note should be lower than 2nd last
		if( n2.tone < n3.tone){
			tally += 5*song.tunes[i].track_length;
		}
		
		resolution_diff = abs(n2.tone - n3.tone);
		// Track should resolve on a major step
		// ie. the step size should be one of four options,
		// a major third, a perfect fifth, a major seventh, or an octave 
		if(resolution_diff != 4 ||
		  resolution_diff != 7 || 
		  resolution_diff != 11 ||
		  resolution_diff != 12){
			tally += 3*song.tunes[i].track_length;
		}
		// Last note should be held for half a measure or longer
		if(n3.hold_time < (BEATS_PER_MEASURE/2)){
			tally += 3*song.tunes[i].track_length;
		}
		
		// Song should end within the same octave that it began
		if(abs(n1.tone - n3.tone) > (NOTES_PER_OCTAVE/2)){
			tally += 5*song.tunes[i].track_length;
		}
		
		for (int k = 0;k < song.tunes[i].track_length;k++) {
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
			
			// Repeating Rests
			if((a3.tone == REST) && (a2.tone == REST))
				tally += 1;

			// If a note is high, we don't want it to repeat
			if (a3.tone > C7_INDEX && a3.tone == a2.tone)
				tally += 1;
	    		
	    		// Must be within an octave of the past two notes, not counting rests
	    		if ((abs(a3.tone - a2.tone) >= NOTES_PER_OCTAVE) && (a2.tone != REST) && (a3.tone != REST))
	    			tally += 2*abs(a3.tone - a2.tone)/NOTES_PER_OCTAVE;
	    		if ((abs(a3.tone - a1.tone) >= NOTES_PER_OCTAVE) && (a2.tone != REST) && (a1.tone != REST))
				tally += 2*abs(a3.tone - a1.tone)/NOTES_PER_OCTAVE;
			
			// Hold Time must stay approx. the same size as for prev notes
			if (!(	a3.hold_time >= a2.hold_time - (NOTES_PER_OCTAVE/2) &&
				a3.hold_time <= a2.hold_time + (NOTES_PER_OCTAVE/2)))
	    			tally += 1;
	    		if (!(	a3.hold_time >= a1.hold_time - (NOTES_PER_OCTAVE/2) &&
				a3.hold_time <= a1.hold_time + (NOTES_PER_OCTAVE/2)))
				tally += 1;
			
			//printf("STEPHEN's STUFF\n");
			if (a3.tone == 0) continue;
			for (int j = 0;j < instruments;j++) {
			    if (j == i) continue;
			    for (int l = 0;l < a3.hold_time;l++) {
				//printf("GET NOTE AT BEAT\n");
				a4 = getNoteAtBeat(song.tunes[j], beat+l);
				//printf("NOTE BEATING COMPLETE\n");
				if (a4.tone == -1 || a4.tone == REST) continue;// This channel has already ended or is at rest
				//printf("FREQ_RATIO for %d and %d\n", a3.tone, a4.tone);
				//printf("FREQS are %d and %d\n", frequencies[a3.tone], frequencies[a4.tone]);
				if (frequencies[a3.tone] > frequencies[a4.tone]) {
				  freq_ratio = floor((100*frequencies[a3.tone]) / frequencies[a4.tone]);
				} else {
				  freq_ratio = floor((100*frequencies[a4.tone]) / frequencies[a3.tone]);
				}
				//printf("FREQ_RATIO DONE\n");
				// If there is dissonance, +2 demerits
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
	score += tally;
	if (score < 0) score = 0;
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
