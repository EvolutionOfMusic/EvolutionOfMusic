#include "C2Wav.h"

void C2Wav(Song song){
    //printf("IN\n");
    double SAMPLING_RATE = (2*44100), j[song.track_num],
        SAMPLING_PERIOD  = 1/SAMPLING_RATE;
    int i = 1, k = 0, m[song.track_num], maxLength = 0, numberOfSamples = 0,
        samplesPerNote = ((int)SAMPLING_RATE*60/((song.tempo == 0) ? 10:song.tempo))/16;
	
    char title[38];
    sprintf(title, "samples_%i", song.song_id);
    printf("START %i\n", song.song_id);
    for(i = 0;i < song.track_num;i++){
        j[i] = 0;m[i] = 0;
        if(song.tunes[k].track_length < song.tunes[i].track_length)
            k = i;
    }
    maxLength = song.tunes[k].track_length;

    for(i = 0;i < maxLength;i++){
        numberOfSamples += (song.tunes[k].channel[i].hold_time*samplesPerNote);
        //printf("%i %i\n", numberOfSamples, song.tunes[k].channel[i].hold_time);
    }
	
    //printf("CALLOCING\n");
    float *finalSong = (float *)calloc(numberOfSamples, sizeof(float));
    double *songArray = (double *)calloc(numberOfSamples, sizeof(double));
    //printf("CALLOCING DONE\n");
    for(i = 0;i < numberOfSamples;i++)
        songArray[i] = 0;
    
    //printf("Big for loop: %lf %i %i\n", SAMPLING_PERIOD, (int)SAMPLING_PERIOD, samplesPerNote);
    for(i = 0;i < numberOfSamples;i++){
        for(k = 0;k < song.track_num;k++){
            if (m[k] >= song.tunes[k].track_length) continue;
                if(j[k] > song.tunes[k].channel[m[k]].hold_time*samplesPerNote/(int)SAMPLING_RATE){
                    //j[k] = j[k] - (double)(song.tunes[k].channel[m[k]].hold_time*samplesPerNote)/SAMPLING_RATE;
                    j[k] = 0; m[k]++;//Go to next Note
			} else{
                j[k] += SAMPLING_PERIOD;
            }
            songArray[i] += .9*sin(2*M_PI*(double)frequencies[song.tunes[k].channel[m[k]].tone]*j[k]/SAMPLING_RATE);
        }
        //if (i > numberOfSamples-3)
        //printf("Iteration: %i < Size:%i\n", i, numberOfSamples);
	    songArray[i] /= song.track_num;
        finalSong[i] = (float)(songArray[i]);//32767);
    }
    write_wav(title, (unsigned long) numberOfSamples, finalSong, (unsigned int)SAMPLING_RATE);

    //printf("FREEING\n");
    free(songArray);
    free(finalSong);
	
    printf("END\n");
}
