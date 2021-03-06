/*
 * C2Wav.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: Stephen, Aaron
 */

#include "C2Wav.h"
const double SAMPLING_RATE = (3*44100);

double getWave(double amplitude, double frequency, double time) {
    return amplitude*sin((2.0*M_PI*frequency*time)/(SAMPLING_RATE));
}

double getAMWave(double amplitude, double modIndex, double carrier, double modulator, double time) {
    return (getWave(amplitude, carrier, time)+(modIndex/2)*(getWave(amplitude, carrier-modulator, time)+getWave(amplitude, carrier+modulator, time)))/2;
	//amplitude*sin(((2.0*M_PI*frequency*time)/(SAMPLING_RATE)))*sin(((1.0*M_PI*frequency*time)/(SAMPLING_RATE)));
}

double getAFMWave(double amplitude, double timbre, double carrier, double frequency, double time, bool AM) {
    double thetaC = ((2.0*M_PI*carrier*time)/(SAMPLING_RATE));
    double thetaF = ((2.0*M_PI*frequency*time)/(SAMPLING_RATE));
    if (AM) {
        return amplitude*sin(thetaC + timbre*(abs(carrier-frequency))*sin(thetaF))*sin(0.5*(thetaC + timbre*(abs(carrier-frequency))*sin(thetaF)));
    } else {
        return amplitude*sin(thetaC + timbre*(abs(carrier-frequency))*sin(thetaF));
    }
}

double getFMWave(double amplitude, double timbre, double carrier, double frequency, double time) {
    return getAFMWave(amplitude, timbre, carrier, frequency, time, false);
    /*double thetaC = ((2.0*M_PI*carrier*time)/(SAMPLING_RATE));
    double thetaF = ((2.0*M_PI*frequency*time)/(SAMPLING_RATE));
    return amplitude*sin(thetaC + timbre*(abs(carrier-frequency))*sin(thetaF));*/
}

double getAccordianWave(double amplitude, double timbre, double frequency, double time) {
    return getFMWave(amplitude, timbre, frequency, frequency/2, time);
}

double getOrganWave(double amplitude, double frequency, double time) {
	return amplitude*sin(((2.0*M_PI*frequency*time)/(SAMPLING_RATE)))*sin(((1.0*M_PI*frequency*time)/(SAMPLING_RATE)));
}

double getBassoonWave(double amplitude, double timbre, double frequency, double time) {
    return getAFMWave(amplitude, 0.005, frequency, 5*frequency+0.5, time, true);
}

double getBrassWave(double amplitude, double timbre, double frequency, double time) {
    return getFMWave(amplitude, timbre, frequency-2, frequency+2, time);
}

double getBellWave(double amplitude, double timbre, double frequency, double time) {
    double GoldenRatio = 1.618033988749895;// Creates Much Noise (Needs Modulation Func)
    return getFMWave(amplitude, timbre, frequency/GoldenRatio, frequency, time);
}

double getWoodBlockWave(double amplitude, double timbre, double frequency, double time) {
    double GoldenRatio = 1.618033988749895;// Creates Much Noise (Needs Modulation Func)
    return getFMWave(amplitude, timbre, frequency*GoldenRatio, frequency, time);
}

void setEnvelope(int type, double* envelope) {
    if (type == 9) {//WoodBlock
        envelope[0] = 1.0;
        envelope[1] = 0.0;
        envelope[2] = 0.0;
        envelope[3] = 0.0;
        envelope[4] = 0.0;
    } else if (type == 4) {//Bell
        envelope[0] = 0.0;
        envelope[1] = 1.0;
        envelope[2] = 0.4;
        envelope[3] = 0.01;
        envelope[4] = 0.0;
    } else if (type == 3) {//Brass
        envelope[0] = 0.0;
        envelope[1] = 1.0;
        envelope[2] = 0.75;
        envelope[3] = 0.6;
        envelope[4] = 0.0;
    } else {//Everything Else
        envelope[0] = 0.0;
        envelope[1] = 1.0;
        envelope[2] = 1.0;        
        envelope[3] = 1.0;
        envelope[4] = 0.0;
    }//This is also needed for WoodWinds
}

double getInstrumentWave(double tempAmp, Track track, Note note, int i, double time, double T, double trackNum, int type) {
    // Instruments
    if (type == 10) {//GUITAR
        return getAccordianWave(tempAmp, 0.01+0.9/(1000*(i-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i)/(trackNum+4);
    } else if (type == 9) {
        return getWoodBlockWave(tempAmp, 1.0/(10000*(i-time)/(SAMPLING_RATE/6)), frequencies[note.tone], i)/(trackNum+4);
    } else if (type == 8) {//HARP
        return getAccordianWave(tempAmp, 0.9/(1000*(i-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i)/(trackNum+4);
    } else if (type == 7) {
        return getAccordianWave(tempAmp, 0.1+0.9/(1000*(i-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i)/(trackNum+4);
    } else if (type == 6) {
	    if (i < 1*SAMPLING_RATE/6 + time) {//WoodWinds Need Mod Func
            return getBassoonWave(tempAmp, 0.5*pow((i-time)/(SAMPLING_RATE/6), 2)/2, frequencies[note.tone], i)/(trackNum+4);
        } else {
            return getBassoonWave(tempAmp, 0.5, frequencies[note.tone], i)/(trackNum+4);
        }
    } else if (type == 5) {
        return getOrganWave(tempAmp, frequencies[note.tone], i)/(trackNum+4);
    } else if (type == 4) {// Bells need a Modulation Func
        return getBellWave(tempAmp, 1.0/(10000*(i-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i)/(trackNum+4);
    } else if (type == 3) {
        if (i < SAMPLING_RATE/6 + time) {
            return getBrassWave(tempAmp, 1*sqrt((i-time)/(SAMPLING_RATE/6)), frequencies[note.tone], i)/(trackNum+4);
        } else if (i < SAMPLING_RATE + time) {
            return getBrassWave(tempAmp, 1-0.6*sqrt((i-(time+(SAMPLING_RATE/6)))/(5*SAMPLING_RATE/6)), frequencies[note.tone], i)/(trackNum+4);
        } else {
            return getBrassWave(tempAmp, 0.4, frequencies[note.tone], i)/(trackNum+4);
        }
    } else if (type == 2) {
        return getAMWave(tempAmp, 1.0, frequencies[note.tone], frequencies[note.tone+12], i)/(trackNum+4);
    } else if (type == 1) {
        return getFMWave(tempAmp, 1.0, frequencies[track.channel[0].tone], frequencies[note.tone], i)/(trackNum+4);
    } else {
        return getWave(tempAmp, frequencies[note.tone], i)/(trackNum+4);
    }
}

double runtime(double hold, double pause, double tempo) {
    return (hold)/tempo;
}

void C2Wav(int type, Song song){
    double numberOfSamples = 0.0, T;
    double tempo = 4.0 * ((song.tempo < 10) ? 10.0:(double)song.tempo) / 60.0;
    int i, j, k, amplitude = 32000;
    int SavedType = type;

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
    numberOfSamples += 5;//For popping correction
    
    //printf("CALLOCING\n");
    double *finalSong = (double *)calloc(numberOfSamples, sizeof(double));
    //printf("CALLOCING DONE\n");
    
    int noteIndex;
    double time, trackNum = ((double)song.track_num), tempAmp;
    double envelope[5];
    setEnvelope(type, envelope);
    Note note; Track track;

    for(k = 0;k < trackNum;k++){
	    noteIndex = 0;time = 0.0;
        printf("Track %d ", k);
        track = song.tunes[k];
        note = track.channel[noteIndex];
        T = runtime(note.hold_time, note.pause_time, tempo);
        //type = (track.instrument_id) % 11;
        if (SavedType == 0) {
            switch ((k == 0) ? 0:((track.instrument_id) % 6)) {
            case 0://WOODBLOCK
                type = 9;
                printf("WOODBLOCK\n");
                break;
            case 1://BELL
                type = 4;
                printf("BELL\n");
                break;
            case 2://ORGAN
                type = 5;
                printf("ORGAN\n");
                break;
            case 3://ACCORDIAN
                type = 7;
                printf("ACCORDIAN\n");
                break;
            case 4://GUITAR
                type = 10;
                printf("GUITAR\n");
                break;
            case 5://HARP
                type = 8;
                printf("HARP\n");
                break;
            }
        } else {
            printf("\n");
        }
        
        amplitude = 32000.0*track.volume/100.0;

        for(i = 0;i < numberOfSamples;i++){
            if (noteIndex >= track.track_length) continue; //Most tracks aren't the longest track
            
            if (i > T*SAMPLING_RATE + time) {
                    // This should solve popping
                    tempAmp = amplitude*(envelope[3]);
                    if (type == 8) {//WOODBLOCK
                        //NOTHING, IT ENDED ALREADY
                    } else if (type == 5) {
                        finalSong[i] += getOrganWave(3.0*tempAmp/4.0, frequencies[note.tone], i)/(trackNum+4);
                        finalSong[i+1] += getOrganWave(tempAmp/2.0, frequencies[note.tone], i+1)/(trackNum+4);
                        finalSong[i+2] += getOrganWave(tempAmp/4.0, frequencies[note.tone], i+2)/(trackNum+4);
                        finalSong[i+3] += getOrganWave(tempAmp/8.0, frequencies[note.tone], i+3)/(trackNum+4);
                    } else if (type == 4) {
                        finalSong[i] += getBellWave(3.0*tempAmp/4.0, 1.0/(10000*(i-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i)/(trackNum+4);
                        finalSong[i+1] += getBellWave(tempAmp/2.0, 1.0/(10000*(i+1-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i+1)/(trackNum+4);
                        finalSong[i+2] += getBellWave(tempAmp/4.0, 1.0/(10000*(i+2-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i+2)/(trackNum+4);
                        finalSong[i+3] += getBellWave(tempAmp/8.0, 1.0/(10000*(i+3-time)/(SAMPLING_RATE/2)), frequencies[note.tone], i+3)/(trackNum+4);
                    } else if (type == 3) {
                        finalSong[i] += getBrassWave(3.0*tempAmp/4.0, 0.4, frequencies[note.tone], i)/(trackNum+4);
                        finalSong[i+1] += getBrassWave(tempAmp/2.0, 0.4, frequencies[note.tone], i+1)/(trackNum+4);
                        finalSong[i+2] += getBrassWave(tempAmp/4.0, 0.4, frequencies[note.tone], i+2)/(trackNum+4);
                        finalSong[i+3] += getBrassWave(tempAmp/8.0, 0.4, frequencies[note.tone], i+3)/(trackNum+4);
                    } else if (type == 2) {
                        finalSong[i] += getAMWave(3.0*tempAmp/4.0, 1.0, frequencies[note.tone], frequencies[note.tone+12], i)/(trackNum+4);
                        finalSong[i+1] += getAMWave(tempAmp/2.0, 1.0, frequencies[note.tone], frequencies[note.tone+12], i+1)/(trackNum+4);
                        finalSong[i+2] += getAMWave(tempAmp/4.0, 1.0, frequencies[note.tone], frequencies[note.tone+12], i+2)/(trackNum+4);
                        finalSong[i+3] += getAMWave(tempAmp/8.0, 1.0, frequencies[note.tone], frequencies[note.tone+12], i+3)/(trackNum+4);
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
            
            // Amplitude Envelope Comprehension
            if (type == 9 || type == 8) {//WOODBLOCK/PERCUSSION || HARP
                if (i < 1*SAMPLING_RATE/48 + time) {
                    tempAmp = amplitude*((i-time)/(SAMPLING_RATE/48));
                } else if (i < 1*SAMPLING_RATE/6 + time) {
                    tempAmp = amplitude*(1-((i-(time+(SAMPLING_RATE/48)))/((SAMPLING_RATE/6)-(SAMPLING_RATE/48))));
                } else {
                    tempAmp = 0;
                }
            } else if (type == 10) {//GUITAR
                if (i < 1*SAMPLING_RATE/48 + time) {
                    tempAmp = amplitude*pow(((i-time)/(SAMPLING_RATE/48)),2);
                } else {
                    tempAmp = amplitude - amplitude*pow((i-(time+SAMPLING_RATE/48))/(T*SAMPLING_RATE-(SAMPLING_RATE/48)), 2);
                }
            } else {
                if (i < 1*SAMPLING_RATE/6 + time) {
                    tempAmp = amplitude*sqrt((i-time)/(SAMPLING_RATE/6));//(envelope[1]-envelope[0])*(i-time)/(SAMPLING_RATE/6);
                } else if (i < 1*SAMPLING_RATE/3 + time) {
                    tempAmp = amplitude*(envelope[1] - (envelope[1]-envelope[2])*(i-(time+(SAMPLING_RATE/6)))/(SAMPLING_RATE/6));
                } else {
                    tempAmp = amplitude*(envelope[2] - (envelope[2]-envelope[3])*(i-(time+SAMPLING_RATE/3))/((T-0.3333)*SAMPLING_RATE));
                }
            }

            finalSong[i] += getInstrumentWave(tempAmp, track, note, i, time, T, trackNum, type);
        }
    }
    printf("NumSamples: %lu\n", (long unsigned)numberOfSamples);
    
    write_wav(title, numberOfSamples, finalSong, SAMPLING_RATE);

    //printf("FREEING\n");
    free(finalSong);
	
    printf("END\n");
}
