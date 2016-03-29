#include "C2Wav.h"

double note(double amplitude, double frequency, double time) {
    return amplitude*cos(2*M_PI*frequency*time);
}

double time(double hold, double pause, double tempo) {
    return (hold)/tempo;
}

void C2Wav(Song song){
    //printf("IN\n");
    double SAMPLING_RATE = (44100), j[song.track_num], T, volume;
    double SAMPLING_PERIOD = 1/SAMPLING_RATE;
    int i = 1, k = 0, m[song.track_num], maxLength = 0, numberOfSamples = 0,
        tempo = 16 * ((song.tempo < 10) ? 10:song.tempo) / 60,
        samplesPerNote = SAMPLING_RATE/tempo;
	
    char title[38];
    sprintf(title, "samples_%i", song.song_id);
    printf("START %i\n", song.song_id);
    for(i = 0;i < song.track_num;i++){
        j[i] = 0;m[i] = 0;
        if(song.tunes[k].track_length < song.tunes[i].track_length) k = i;
    }
    maxLength = song.tunes[k].track_length;

    for(i = 0;i < maxLength;i++) numberOfSamples += (song.tunes[k].channel[i].hold_time*samplesPerNote);
    numberOfSamples++;//For popping correction
	
    //printf("CALLOCING\n");
    float *finalSong = (float *)calloc(numberOfSamples, sizeof(float));
    //printf("CALLOCING DONE\n");
    
    for(i = 0;i < numberOfSamples;i++) finalSong[i] = 0;
    
    for(i = 0;i < numberOfSamples;i++) {
        for(k = 0;k < song.track_num;k++) {
            if (m[k] >= song.tunes[k].track_length) continue; //Most tracks aren't the longest track
            volume = 90.0/100;//((double)song.tunes[k].volume)/100;
            T = time(song.tunes[k].channel[m[k]].hold_time, 
                    song.tunes[k].channel[m[k]].pause_time, 
                    tempo);
            if(j[k] > T) {
                    // This should solve popping
                    finalSong[i] += note(volume/2,                                      //Amplitude
                                        frequencies[song.tunes[k].channel[m[k]].tone],  //Frequency
                                        T)/(song.track_num+1.0);                        //Time
                    
                    j[k] = 0; m[k]++;//Go to next Note
                    if (m[k] >= song.tunes[k].track_length) continue;
            } else {
                j[k] += SAMPLING_PERIOD;
            }
            finalSong[i] += note(volume, 
                                frequencies[song.tunes[k].channel[m[k]].tone], 
                                j[k]/(SAMPLING_RATE))/(song.track_num+1.0); 
        }
    }
    write_wav(title, numberOfSamples, finalSong, SAMPLING_RATE);

    //printf("FREEING\n");
    free(finalSong);
	
    printf("END\n");
}
