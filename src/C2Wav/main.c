#include "../song_structs.h"
#include "C2Wav.h"
#include "make_wav.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* 
#define S_RATE  (44100)
#define BUF_SIZE (S_RATE*10) /* 2 second buffer /
 
int buffer[BUF_SIZE];
 
int main(int argc, char ** argv)
{
    int i;
    float t;
    float amplitude = 32000;
    float freq_Hz = 440;
    float phase=0;
 
    float freq_radians_per_sample = freq_Hz*2*M_PI/S_RATE;
 
    /* fill buffer with a sine wave /
    for (i=0; i<BUF_SIZE; i++)
    {
        phase += freq_radians_per_sample;//+((i/100%100)*(i/100%100))*2*M_PI/S_RATE;
    buffer[i] = (int)(amplitude * sin(phase));
    }
 
    write_wav("test.wav", BUF_SIZE, buffer, S_RATE);
 
    return 0;
}

/*/
Track generateRandomTrack(int ID, int volume);

int main(int argc, char ** argv){
	Song song;
	song.tunes[0] = generateRandomTrack(0,128);
	song.tunes[1] = generateRandomTrack(1,128);
	song.tunes[2] = generateRandomTrack(2,128);
	song.song_id = 0;
	song.tempo = 60;
	song.track_num = 3;

	C2Wav(song);
}

Track generateRandomTrack(int ID, int volume){
	Track newTrack;	Note newNote;
	int i = 0, j = 0;
	time_t t;
	srand((unsigned) time(&t));
//	printf("before id\n");
	newTrack.instrument_id = (rand()%(ID+1));//INSTRUMENT_TYPES%INSTRUMENT_NUMBER;
//	printf("after id\n");
	Song tempSong;
	newTrack.volume = volume;
	//these first two notes may cause the song to always get a score of 0

	while(j < MAX_NOTES){
		newNote.pause_time = rand()%2; 

		switch(ID){
			case(0):
				newNote.tone = (84-i)%96+10;
				newNote.hold_time = (2+i/3)%16+1; 
				break;
			case(1):
				newNote.tone = (20+i)%96;
				newNote.hold_time = (6-((i/2)%4))%16+1; 
				break;
			case(2):
				newNote.tone = ((18+i*i/10-5/((i+3)/3))%48)+10;
				newNote.hold_time = 3; 
				break;
		}
		//newNote.tone = 32;
		//newNote.hold_time = 16;

//		printf("hold_time: %i\n", newNote.hold_time);
		if((j+newNote.hold_time)>MAX_NOTES){
			newNote.hold_time = MAX_NOTES-j;
		}
		//newNote.tone = rand()%NUMBER_OF_TONES;
		newTrack.channel[i++] = newNote;
		j += newNote.hold_time;
		printf("%i: %i %i\n", i, newNote.tone, newNote.hold_time);
	}
	newTrack.track_length = i;
//	printf("track length: %i\n", newTrack.track_length);;
	return newTrack;
}//
