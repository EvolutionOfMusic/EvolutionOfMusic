/*
 * slow_critic_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "critic_shell.h"
#include <fstream>
#include <iostream>

const int NOTES_PER_OCTAVE = 12;
const int BEATS_PER_MEASURE = 16;
const int C6_INDEX = 6 * NOTES_PER_OCTAVE + 1;
const int C5_INDEX = 5 * NOTES_PER_OCTAVE + 1;
const int C3_INDEX = 3 * NOTES_PER_OCTAVE + 1;

/* A Song holds Tracks; A Track holds Notes
 * Consonance is good; Dissonance is bad
 * https://en.wikipedia.org/wiki/Consonance_and_dissonance
 * https://musicmasterworks.com/WhereMathMeetsMusic.html
 * https://en.wikipedia.org/wiki/Pythagorean_tuning
 * http://hyperphysics.phy-astr.gsu.edu/hbase/music/mussca.html
 * - Also used for transitions
 */
const int CONSONANCE = 600;
const int CONSONANCE_RANGE = 8;
/* Rhythm
 * - Being on the same beat is good
 * - 4/4 Time is good
 */
const int PERFECT_TIME = 5000;
const int FOURFOUR_TIME = 200000;
const int MORE_RESTS = 20;
/* Length
 * - Slower notes for faster songs
 * - Faster notes for slower songs
 * - Less repeating tones
 * - More repeating hold times
 * - Stay within the Octave
 */
const int FAST_TEMPO_MARKER = 100;
const int SLOW_TEMPO_MARKER = 60;
const int TEMPO_SCALING = 20;
const int REPEATING_NOTES = 1000;
const int OCTAVE_RETENTION = 100;
 /* START OF SONG
  * - Don't start Silently
  */
const int SILENT_START = 1000;
 /* END OF SONG
  * - Songs should end around the same time
  * - Should end with a step down
  * - Should end with a major step
  * - Should end on a longer note length
  */
const int TRAILING_NOTES = 50;
const int END_STEP_DOWN = 100;
const int END_MAJOR_STEP = 100;
const int END_LONGER = 100;
// - Less tracks should be discouraged
const int TRACK_MARKER = 4;

long long c_shell(Song song) {
	long long score = 100;
       	score = supervisor(song);
	return score;
}

long long supervisor(Song song) {
	//JUDGE IT
        long long endTally = 0, consonanceTally = 0, repeatingTally = 0,
	        rhythmTally = 0, noteLengthTally = 0, restTally = 0, octaveTally = 0, trackTally = 0,
	        instruments = song.track_num, beat, resolution_diff;
	float freq_ratio;
	bool check = false;
	Note a1, a2, a3, a4, n1, n2, n3;
	
	// We want songs with more tracks
	if (instruments < TRACK_MARKER)
		trackTally += pow(TRACK_MARKER+2 - instruments, 10);
	
	for (int i = 0;i < instruments;i++) {
	        if (song.tunes[i].channel[0].tone != REST) check = true;
		beat = 0;
		
		n1 = song.tunes[i].channel[0];
		n2 = song.tunes[i].channel[song.tunes[i].track_length - 2];
		n3 = song.tunes[i].channel[song.tunes[i].track_length - 1];
	        
		// Track has poor ending, last note should be lower than 2nd last
		if (n2.tone < n3.tone)
			endTally += END_STEP_DOWN;
		
		resolution_diff = abs(n2.tone - n3.tone);
		// Track should resolve on a major step
		// ie. the step size should be one of four options,
		// a major third, a perfect fifth, a major seventh, or an octave 
		if (resolution_diff != 4 ||
		    resolution_diff != 7 || 
		    resolution_diff != 11 ||
		    resolution_diff != NOTES_PER_OCTAVE)
			endTally += END_MAJOR_STEP;
		
		
		// Last note should be held for half a measure or longer
		if(n3.hold_time < (BEATS_PER_MEASURE/2))
			endTally += END_LONGER;
		
		// Song should end within the same octave that it began
		if(abs(n1.tone - n3.tone) > (NOTES_PER_OCTAVE/2))
			endTally += OCTAVE_RETENTION*song.tunes[i].track_length;
		
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
			
			// tempo_alt is at most 20 at least 0
			if (song.tempo > FAST_TEMPO_MARKER && a3.hold_time < BEATS_PER_MEASURE/2) {
				//Fast
				noteLengthTally += TEMPO_SCALING*((BEATS_PER_MEASURE/2)-a3.hold_time);
			} else if (song.tempo < SLOW_TEMPO_MARKER && a3.hold_time > BEATS_PER_MEASURE/2) {
				//Slow
				noteLengthTally += TEMPO_SCALING*(a3.hold_time-(BEATS_PER_MEASURE/2));
			}

			if (a3.tone == REST && a3.hold_time >= 8)
			        restTally += MORE_RESTS;
			// if note is short; PUNISH HIM
			if (a3.hold_time < 4)
				noteLengthTally += 10*(6-a3.hold_time);
			if (a3.hold_time == 0)
				noteLengthTally += SILENT_START*SILENT_START;
			
			// 4/4 time; STAY ON BEAT
			if (a3.hold_time != 0 && beat % a3.hold_time != 0)
				rhythmTally += FOURFOUR_TIME;
			
			// Repeating Rests
			if((a3.tone == REST) && (a2.tone == REST)) {
				restTally += REPEATING_NOTES/2;
				repeatingTally += REPEATING_NOTES/2;
			}

			// If a note is high, we don't want it to repeat
			if (a3.tone > C6_INDEX && a3.tone == a2.tone) {
				repeatingTally += REPEATING_NOTES/2;
				octaveTally += REPEATING_NOTES/2;
			}

			// A note is high
			if (a3.tone > C6_INDEX-(NOTES_PER_OCTAVE/2)) {
				octaveTally += 10;//*REPEATING_NOTES*REPEATING_NOTES;
				//octaveTally += pow(a3.tone - (C5_INDEX-(NOTES_PER_OCTAVE/2)), 2);
			}

			// Low notes
			if (a3.tone != REST && a3.tone < C3_INDEX) {
				octaveTally += 10;//*REPEATING_NOTES;
				//octaveTally += pow(C3_INDEX - a3.tone, 2);
			}

			/*if (k > 1 && !(a1.tone == REST || a2.tone == REST || a3.tone == REST))
				restTally += MORE_RESTS;*/
	    		
			// Must be within an octave of the past two notes, not counting rests
			if ((abs(a3.tone - a2.tone) >= NOTES_PER_OCTAVE) && (a3.tone != REST) && (a2.tone != REST))
				octaveTally += OCTAVE_RETENTION*abs(a3.tone - a2.tone)/NOTES_PER_OCTAVE;
			if ((abs(a3.tone - a1.tone) >= NOTES_PER_OCTAVE) && (a3.tone != REST) && (a1.tone != REST))
				octaveTally += OCTAVE_RETENTION*abs(a3.tone - a1.tone)/NOTES_PER_OCTAVE;
			
			// Hold Time must stay approx. the same size as for prev notes
			if (abs(a3.hold_time - a2.hold_time) > (NOTES_PER_OCTAVE/4))
				noteLengthTally += REPEATING_NOTES;
			if (abs(a3.hold_time - a2.hold_time) > (NOTES_PER_OCTAVE/4))
				noteLengthTally += REPEATING_NOTES;
			
			if (a3.tone == REST) {
				beat += a3.hold_time;
				continue;
			}
			
			for (int j = 0;j < instruments;j++) {
			    if (j == i) continue;
			    for (int l = 0;l < a3.hold_time;l++) {
			        a4 = getNoteAtBeat(song.tunes[j], beat+l);
				
				if (a4.tone == -1 || a4.tone == REST) {
					endTally += TRAILING_NOTES;
					continue;// This channel has already ended or is at rest
				}
				//if (l == 0 && !(a4.pause_time == 3) && (beat % 4 != 0)) 
				//	rhythmTally += PERFECT_TIME;// Perfect Time is good

				if (frequencies[a3.tone] > frequencies[a4.tone]) {
					freq_ratio = floor((100*frequencies[a3.tone]) / frequencies[a4.tone]);
				} else {
					freq_ratio = floor((100*frequencies[a4.tone]) / frequencies[a3.tone]);
				}
				
				if (freq_ratio > 200)
				        for (int k = 0;k < (freq_ratio / 100)-1;k++)
				                freq_ratio -= 100;
				
				// If there is dissonance, + demerits
				if (!(  ((freq_ratio < 200 + CONSONANCE_RANGE) && 
					(freq_ratio > 200 - CONSONANCE_RANGE)) || // 2:1
				        ((freq_ratio < 150 + CONSONANCE_RANGE) && 
					(freq_ratio > 150 - CONSONANCE_RANGE)) || // 3:2
				        ((freq_ratio < 133 + CONSONANCE_RANGE) && 
					(freq_ratio > 133 - CONSONANCE_RANGE)) || // 4:3
				        ((freq_ratio < 100 + CONSONANCE_RANGE) && 
					(freq_ratio > 100 - CONSONANCE_RANGE)))) { //Octaves
				        consonanceTally += CONSONANCE;
					//printf("CONS %f\n", freq_ratio);
				}
			    }
			}
			beat += a3.hold_time;
		}
	}
	
	if (!check) restTally += SILENT_START;
	
	std::ofstream file("critic_output", std::ios_base::app);
	if (file.is_open()) {
		file << "End " << endTally << "\n"; 
		file << "Consonance " << consonanceTally << "\n";
		file << "Rhythm " << rhythmTally << "\n";
		file << "Note Length " << noteLengthTally << "\n";
		file << "Rests " << restTally << "\n"; 
		file << "Octaves " << octaveTally << "\n";
		file << "Track " << trackTally << "\n";
		file.close();
	}
	
	return endTally + consonanceTally + rhythmTally + noteLengthTally + restTally + octaveTally + trackTally;
}

Note getNoteAtBeat(Track track, int beat) {
        int o = -1, temp_beat = 0;
       	while (temp_beat < beat && o < track.track_length) {
       	    o++;
	    temp_beat += track.channel[o].hold_time;
       	}
	if (o == track.track_length) {Note n;n.tone = -1;return n;} 
	Note got = track.channel[o];
	if (temp_beat - track.channel[o].hold_time == beat)
		got.pause_time = 3;//Was perfectly timed
	return got;
}

int manual_override(Song song) {
	//JUDGE IT
	int score = 0;

	//UI Interactions
	//TODO

	return score;
}
