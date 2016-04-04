#include "C2Wav.h"
const double SAMPLING_RATE = (2*44100);

double getWave(double amplitude, double frequency, double time) {
    return amplitude*sin((2.0*M_PI*frequency*time)/(SAMPLING_RATE));
}

double getAMWave(double amplitude, double frequency, double time) {
    return amplitude*sin(((2.0*M_PI*frequency*time)/(SAMPLING_RATE)))*sin(((1.0*M_PI*frequency*time)/(SAMPLING_RATE)));
}

double getFMWave(double amplitude, double timbre, double carrier, double frequency, double time) {
    double thetaC = ((2.0*M_PI*carrier*time)/(SAMPLING_RATE));
    double thetaF = ((2.0*M_PI*frequency*time)/(SAMPLING_RATE));
    return amplitude*sin(thetaC + timbre*(abs(carrier-frequency))*sin(thetaF));
}

double getBrassWave(double amplitude, double frequency, double time) {
    return getFMWave(amplitude, 1.0, frequency, frequency, time);
}

double getBellWave(double amplitude, double timbre, double frequency, double time) {
    double GoldenRatio = 1.618033988749895;
    return getFMWave(amplitude, timbre, frequency/GoldenRatio, frequency, time);
}

double runtime(double hold, double pause, double tempo) {
    return (hold)/tempo;
}

void C2Wav(int type, Song song){
    double numberOfSamples = 0.0, T;
    double tempo = 4.0 * ((song.tempo < 10) ? 10.0:(double)song.tempo) / 60.0;
    int i, j, k, amplitude = 32000;
	
    char title[38];
    sprintf(title, "samples_%i.wav", song.song_id);
    printf("START %i\n", song.song_id);
    k = 0;
    int maxNoteCount = 0, noteCount;
    for(i = 0;i < song.track_num;i++) {
        noteCount = 0;
        for (j = 0;j < song.tunes[i].track_length;j++)
            noteCount += song.tunes[i].channel[j].hold_time;
        if (noteCount > maxNoteCount) maxNoteCount = noteCount;
    }
    
    numberOfSamples = (runtime(maxNoteCount, 0.0, tempo)*SAMPLING_RATE);
    numberOfSamples+=5;//For popping correction
	
    //printf("CALLOCING\n");
    double *finalSong = (double *)calloc(numberOfSamples, sizeof(double));
    //printf("CALLOCING DONE\n");
    
    int noteIndex;
    double time, trackNum = ((double)song.track_num), tempAmp;
    double envelope[5];
    if (type == 4) {//Bell
        envelope[0] = 0.0;
        envelope[1] = 1.0;
        envelope[2] = 0.5;
        envelope[3] = 0.2;
        envelope[4] = 0.0;
    } else if (type == 3) {//Brass
        envelope[0] = 0.0;
        envelope[1] = 1.0;
        envelope[2] = 0.75;
        envelope[3] = 0.6;
        envelope[4] = 0.0;
    } else {
        envelope[0] = 0.0;
        envelope[1] = 1.0;
        envelope[2] = 1.0;        
        envelope[3] = 1.0;
        envelope[4] = 0.0;
    }
    Note note; Track track;

    for(k = 0;k < trackNum;k++){
	    noteIndex = 0;time = 0.0;
        printf("Track %d %f\n", k, trackNum);
        track = song.tunes[k];
        note = track.channel[noteIndex];
        T = runtime(note.hold_time, note.pause_time, tempo);
        //type = (track.instrument_id) % 4;
        //amplitude = 32000.0*track.volume/100.0;

        for(i = 0;i < numberOfSamples;i++){
            if (noteIndex >= track.track_length) continue; //Most tracks aren't the longest track
            
            if (i > T*SAMPLING_RATE + time) {
                    // This should solve popping
                    tempAmp = amplitude*(envelope[3]-envelope[4]);
                    if (type == 2) {
                        finalSong[i] += getAMWave(3.0*tempAmp/4.0, frequencies[note.tone], i)/(trackNum+4);
                        finalSong[i+1] += getAMWave(tempAmp/2.0, frequencies[note.tone], i+1)/(trackNum+4);
                        finalSong[i+2] += getAMWave(tempAmp/4.0, frequencies[note.tone], i+2)/(trackNum+4);
                        finalSong[i+3] += getAMWave(tempAmp/8.0, frequencies[note.tone], i+3)/(trackNum+4);
                    } else if (type == 1) {
                        finalSong[i] += getFMWave(3.0*tempAmp/4.0, 1.0, frequencies[track.channel[0].tone], 
                                                    frequencies[note.tone], i)/(trackNum+4);
                        finalSong[i+1] += getFMWave(tempAmp/2.0, 1.0, frequencies[track.channel[0].tone], 
                                                    frequencies[note.tone], i+1)/(trackNum+4);
                        finalSong[i+2] += getFMWave(tempAmp/4.0, 1.0, frequencies[track.channel[0].tone], 
                                                    frequencies[note.tone], i+2)/(trackNum+4);
                        finalSong[i+3] += getFMWave(tempAmp/8.0, 1.0, frequencies[track.channel[0].tone], 
                                                    frequencies[note.tone], i+3)/(trackNum+4);
                    } else {
                        finalSong[i] += getWave(3.0*tempAmp/4.0, frequencies[note.tone], i)/(trackNum+4);
                        finalSong[i+1] += getWave(tempAmp/2.0, frequencies[note.tone], i+1)/(trackNum+4);
                        finalSong[i+2] += getWave(tempAmp/4.0, frequencies[note.tone], i+2)/(trackNum+4);
                        finalSong[i+3] += getWave(tempAmp/8.0, frequencies[note.tone], i+3)/(trackNum+4);
                    }
                    
                    time += T*SAMPLING_RATE; 
                    noteIndex++;//Go to next Note
                    if (noteIndex >= track.track_length) continue;
                    note = track.channel[noteIndex];
                    T = runtime(note.hold_time, note.pause_time, tempo);
            }
            
            if (i < 1*SAMPLING_RATE/6 + time) {
                tempAmp = amplitude*(envelope[1]-envelope[0])*(i-time)/(SAMPLING_RATE/6);
            } else if (i < 1*SAMPLING_RATE/3 + time) {
                tempAmp = amplitude*(envelope[1] - (envelope[1]-envelope[2])*(i-(time+(SAMPLING_RATE/6)))/(SAMPLING_RATE/6));
            } else {
                tempAmp = amplitude*(envelope[2] - (envelope[2]-envelope[3])*(i-(time+SAMPLING_RATE/3))/((T-0.3333)*SAMPLING_RATE));
            }
            //printf("%d, amp %f\n", i, tempAmp);

            if (type == 4) {
                double index1 = ((i-time)/(T*SAMPLING_RATE/5));
                if (fmod(index1,1.0) != 0) {
                    finalSong[i] += getBellWave(tempAmp, ((i-time)/(T*SAMPLING_RATE))*(envelope[(int)index1]-envelope[(int)index1-1])/2, frequencies[note.tone], i)/(trackNum+4);
                } else {
                    finalSong[i] += getBellWave(tempAmp, ((i-time)/(T*SAMPLING_RATE))*envelope[(int)index1], frequencies[note.tone], i)/(trackNum+4);
                }
            } else if (type == 3) {
                finalSong[i] += getBrassWave(tempAmp, frequencies[note.tone], i)/(trackNum+4);
            } else if (type == 2) {
                finalSong[i] += getAMWave(tempAmp, frequencies[note.tone], i)/(trackNum+4);
            } else if (type == 1) {
                finalSong[i] += getFMWave(tempAmp, 1.0, frequencies[track.channel[0].tone], frequencies[note.tone], i)/(trackNum+4);
            } else {
                finalSong[i] += getWave(tempAmp, frequencies[note.tone], i)/(trackNum+4);
            }
        }
    }
    printf("NumSamples: %lu\n", (long unsigned)numberOfSamples);
    
    write_wav(title, numberOfSamples, finalSong, SAMPLING_RATE);

    //printf("FREEING\n");
    free(finalSong);
	
    printf("END\n");
}
