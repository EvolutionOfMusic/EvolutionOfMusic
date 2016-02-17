/*
 * song_structs.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen, Aaron
 */

#ifndef SONG_STRUCTS_H_
#define SONG_STRUCTS_H_

#include "frequencies.h"

// IMPORTANT DEFINITIONS
#define NUM_MEASURES 10

#define NOTES_PER_MEASURE 16
#define MAX_NOTES (NOTES_PER_MEASURE*NUM_MEASURES)
#define MAX_NOTE_LENGTH NOTES_PER_MEASURE // 1 measure

#define MAX_TEMPO 120 //bpm
#define MIN_TEMPO 40

#define BYTES_PER_SECOND 12500000
#define MAX_INSTRUMENTS 99

#define INSTRUMENT_TYPES 1
#define NUMBER_OF_TONES NUM_FREQ
// END OF IMPORTANT DEFINITIONS

typedef struct{
	short int pause_time, 	// 1/16th beat, at the moment
			  hold_time;	// 1/16th beat, at the moment
	int       tone;			// 0-95
} Note;

typedef struct{
	int  instrument_id,
	     volume;
	Note channel[MAX_NOTES+1];
} Track;

typedef struct{
	int   song_id,
	      tempo;
	Track tunes[MAX_INSTRUMENTS+1];
} Song;


#endif /* SONG_STRUCTS_H_ */
