/*
 * song_structs.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#ifndef SONG_STRUCTS_H_
#define SONG_STRUCTS_H_

// IMPORTANT DEFINITIONS
#define NUM_MEASURES 10

#define MAX_NOTES 16*NUM_MEASURES
#define MAX_NOTE_LENGTH 1 // measure

#define MAX_TEMPO 120 //bpm
#define MIN_TEMPO 40
// END OF IMPORTANT DEFINITIONS

struct Note {
	long int pause_time,
			 hold_time,
			 tone;
};

struct Track {
	long int instrument_id,
			 volume;
	Note channel[];
};

struct Song {
	long int song_id,
			 tempo;
	Track tunes[];
};


#endif /* SONG_STRUCTS_H_ */
