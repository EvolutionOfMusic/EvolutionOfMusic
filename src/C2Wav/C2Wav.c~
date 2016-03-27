#include "C2Wav.h"

void C2Wav(Song song){
	double SAMPLING_RATE = (44100*2), j[song.track_num], temp;
	double SAMPLING_PERIOD  = 1/SAMPLING_RATE;
	int i = 1, k, m[song.track_num], maxLength = 0, numberOfSamples = 0;
	int samplesPerNote = ((int)SAMPLING_RATE*60/song.tempo)/4;
	char title[38]; 
	sprintf(title, "samples_%i", song.song_id);
	for(i = 0; i < song.track_num; i++){
		j[i] = 0;
		m[i] = 0;
		if(maxLength < song.tunes[i].track_length){
			maxLength = song.tunes[i].track_length;
			k = i;
		}
	}

	for(i = 0; i< maxLength; i++){
		temp += (double)(song.tunes[k].channel[i].hold_time*samplesPerNote);
		printf("%lf %i\n", temp, song.tunes[k].channel[i].hold_time);
	}
	numberOfSamples = (int)temp;
	int *finalSong = malloc(sizeof(int)*numberOfSamples);
	double *songArray = malloc(sizeof(double)*numberOfSamples);
	for(i = 0; i< numberOfSamples; i++){
		songArray[i] = 0;
	}
	printf("Big for loop: %lf %lf %i %i\n", SAMPLING_PERIOD, temp, (int)SAMPLING_PERIOD, samplesPerNote);
	for(i = 0; i < numberOfSamples; i++){
		for(k = 0; k < song.track_num; k++){
			if(j[k] > song.tunes[k].channel[m[k]].hold_time*samplesPerNote/(int)SAMPLING_RATE){
				j[k] = j[k] - (double)(song.tunes[k].channel[m[k]].hold_time*samplesPerNote)/SAMPLING_RATE;
				m[k]++;//Got to next Note
			} else{
				j[k] += SAMPLING_PERIOD;
			}
			
			songArray[i] += .9*sin(2*M_PI*(double)frequencies[song.tunes[k].channel[m[k]].tone]*j[k]/SAMPLING_RATE);
        }
		songArray[i] /= song.track_num;
		finalSong[i] = (int)(songArray[i]*2147483647);
		//printf("%i: %lf %i\n", i, songArray[i], finalSong[i]);
    }
	//printf("%lf\n", temp);
	write_wav(title, (unsigned long) numberOfSamples, finalSong, (unsigned int)SAMPLING_RATE);	

	/*for(i = 0; i< maxLength; i++){
		for(k = 0; k < song.track_num; k++){
			
			if(j[k] > song.tunes[i].channel[m[k]].hold_time){
				j[k] = j[k] - floor(j[k]);
				m[k] += 1;
			} else{
				j[k] += SAMPLING_PERIOD;
			}
			
            songArray[i] += .9*sin(2*M_PI*frequencies[song.tunes[i].channel[m[k]].tone]*j[k]);
        }
		songArray[i]/song.track_num;
    }
	write_wav(title, maxLength, songArray, SAMPLING_RATE);*/
}
