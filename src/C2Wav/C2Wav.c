#include "C2Wav.h"

double note(double amplitude, double frequency, double time) {
    return amplitude*sin(2*M_PI*frequency*time);
}

double time(double hold, double pause, double tempo) {
    return (hold-(pause/2))/tempo;
}

void C2Wav(Song song){
    //printf("IN\n");
    double SAMPLING_RATE = (2*44100), j[song.track_num];
    double SAMPLING_PERIOD  = 1/SAMPLING_RATE, T;
    int i = 1, k = 0, m[song.track_num], maxLength = 0, numberOfSamples = 0,
        tempo = 16 * ((song.tempo == 0) ? 10:song.tempo) / 60,
        samplesPerNote = SAMPLING_RATE/tempo;
	
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
    numberOfSamples++;//For popping correction
	
    //printf("CALLOCING\n");
    float *finalSong = (float *)calloc(numberOfSamples, sizeof(float));
    //printf("CALLOCING DONE\n");
    
    for(i = 0;i < numberOfSamples;i++) finalSong[i] = 0;
    
    //printf("Big for loop: %lf %i %i\n", SAMPLING_PERIOD, (int)SAMPLING_PERIOD, samplesPerNote);
    for(i = 0;i < numberOfSamples;i++){
        for(k = 0;k < song.track_num;k++){
            if (m[k] >= song.tunes[k].track_length) continue; //Most tracks aren't the longest track
            T = time(song.tunes[k].channel[m[k]].hold_time, song.tunes[k].channel[m[k]].pause_time, tempo);
            if(j[k] > T) {
                    finalSong[i] += note(0.9/2, //Amplitude
                                        frequencies[song.tunes[k].channel[m[k]].tone], //Frequency
                                        T)/song.track_num; //Time  // This should solve popping
                    j[k] = 0; m[k]++;//Go to next Note
            } else{
                j[k] += SAMPLING_PERIOD;
            }
            finalSong[i] += note(0.9, frequencies[song.tunes[k].channel[m[k]].tone], j[k]/SAMPLING_RATE)/song.track_num; 
            // j[k]/SAMPLING_RATE <- Works but shouldn't
        }
    }
    write_wav(title, (unsigned long) numberOfSamples, finalSong, (unsigned int)SAMPLING_RATE);

    //printf("FREEING\n");
    free(finalSong);
	
    printf("END\n");
}
