#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ATOMSPACE/opencog/opencog/cogserver/server/CogServer.h>
#include <ATOMSPACE/opencog/opencog/cogserver/server/Factory.h>
#include <ATOMSPACE/cogutils/opencog/util/Logger.h>
#include <ATOMSPACE/atomspace/opencog/atomspace/SimpleTruthValue.h>
#include "song_structs.h"
#include "frequencies.h"

int AGImain(){
	int i, j, k;
	char * currentNode = findCurrentNode();
	Track currentTrack[INSTRUMENT_TYPES];
	//Song currentSong = generateRandomSong(0,127,1);
	//Song comparisonSong = generateRandomSong(1,127,1);
	for(i=0 i<INSTRUMENT_TYPES; i++){
		//the for loops below are for finding all 14.8T note combinations, do not use unless you are certain you want
		//to store this much data.
		/*for(j=0; j<MAX_NOTE_LENGTH; j++){
			for(k=0; k<MAX_NOTE_LENGTH; k++){*/
		for(j=0; j<1; j++){
			for(k=0; k<1; k++)
				findNotePair(i,j,k);
			}
		}
		for(j=0; j<1; j++){
			for(k=0; k<1; k++)
				findCosonance(i,j,k);
			}
		}
	}
}

Song generateRandomSong(int ID, int volume, int numberOfInstruments){
	Song newSong;
	int BPM = MIN_TEMPO+(MAX_TEMPO-MIN_TEMP)*rand();
	newSong.song_id = ID;
	for(i=0; i<numberOfInstruments; i++)
		newSong.tunes[i] = generateRandomTrack(i, volume);
	newSong.tunes[numberOfInstruments] = '\0';
	return newSong;
}

//Apply current node to 
Track generateRandomTrack(int ID, int volume, int firstPauseTime, int firstHoldTime, int secondPauseTime, int secondHoldTime){
	Track newTrack;	Note newNote;
	int i = 3, j = 0;
	newTrack.instrument_id = INSTRUMENT_NUMBER*(ID+rand())/INSTRUMENT_TYPES%INSTRUMENT_NUMBER;
	Song tempSong;
	//these first two notes may cause the song to always get a score of 0

	tempSong.tunes[0].channel[0].pause_time = firstPauseTime; 
	tempSong.tunes[0].channel[0].hold_time = firstHoldTime;
	tempSong.tunes[0].channel[0].tone = 0;

	tempSong.tunes[0].channel[1].pause_time = secondPauseTime; 
	tempSong.tunes[0].channel[1].hold_time = secondholdTime;
	tempSong.tunes[0].channel[1].tone = 0;

	j+= firstPauseTime+firstHoldTime+secondPauseTime+secondHoldTime;
	do{
		while(j<MAX_NOTES){
			newNote.pause_time = MAX_NOTE_LENGTH*rand(); 
			newNote.hold_time = MAX_NOTE_LENGTH*rand();  
			if((j+newNote.hold_time)>MAX_NOTES){
				newNote.hold_time = MAX_NOTES-j;
				newNote.pause_time = 0;
			}
			if((j+newNote.hold_time+newNote.pause_time)>MAX_NOTES){
				newNote.pause_time = MAX_NOTES-newNote.hold_time-j;
			}
			newNote.tone = TONE_NUMBER * rand();
			newTrack.channel[i++] = newNote;
			newTrack.volume = volume;
			j += newNote.pause_time + newNote.hold_time;
		}
		newTrack.channel[i] = '\0';
		tempSong.tunes[0] = newTrack;
		j = 0; i = 0;
	}while(critic(tempSong) == 0);
	return newTrack;
}

Track decoupleNotePair(Song importantSong, Song testSong, int instrumentIndex, char* currentNode){
	int score[6], i, song_id;
	Song tempSongs[5]; 
	tempSong[0].tunes[0] = importantSong[instrumentIndex];
	tempSong[0].tunes[1] = testSong[instrumentIndex];

	tempSong[1].tunes[0] = importantSong[instrumentIndex];
	tempSong[1] = trackSkipper(testSong, instrumentIndex, 1);


	tempSong[2].tunes[0] = testSong[instrumentIndex];
	tempSong[2] = trackSkipper(importantSong, instrumentIndex, 1);	

	tempSong[3] = trackSkipper(importantSong, instrumentIndex, 1);

	song_id = tempSong[3].song_id-1;
	
	tempSong[4] = trackSkipper(importantSong, instrumentIndex, song_id);

	for(i = 0; i<tempSong; i++){
		tempSong[3].tunes[song_id+i] = tempSong[4].tunes[song_id+i];
	}
		
	//submit the following songs to the critic;
	score[0] = critic(importantSong);
	score[1] = critic(testSong);
	score[2] = critic(tempSong[0]);
	score[3] = critic(tempSong[1]);
	score[4] = critic(tempSong[2]);
	score[5] = critic(tempSong[3]);
		
}

Song trackSkipper(Song insertSong, int skipID, int startAddIndex){
	int i;
	Song tempSong;
	for(i=0; i<skipID; i++){
		tempSong.tunes[i+startInsertIndex] = insertSong.tunes[i];
	}
	while(testSong.tunes[i+startIndex] != '\0'){
		tempSong.tunes[i+startInsertIndex] = insertSong.tunes[i+1];
		i++;
	}
	tempSong.tunes[i] = '\0';
	tempSong.song_id = i;
	return tempSong;
}

void findNotePair(int instrumentType, Note firstNote, Note secondNote){
	Note subTrack1[2], subTrack2[MAX_NOTES],subTrack3[MAX_NOTES], subTrack4[MAX_NOTES];
	int i, j, score[NUMBER_OF_TONES], baseScore, AGIKnowldege = 0, 
	maxScore, submitScore;
	Song testSong;

	//needs 

			

			testSong.tunes[0] = generateRandomTrack(0, 127, firstNote.pause_time, firstNote.hold_time, secondNote.pause_time, secondNote.hold_time);

	for(j=0; j<NUMBER_OF_TONES; j++){
		testSong.tunes[0].channel[1].tone = j;
		maxScore = 0;		

		//query the AtomSpace if it knows about the track
		if(SCHEMEBOOLEAN()){
			AGIKnowledge = 1;
			baseScore = evaluator.apply("SUBTRACTSCORE", arg);
		}

		for(i=1; i<NUMBER_OF_TONES; i++){
			testSong.tunes[0].channel[0].tone = i;
			score[i] = critic(testSong);
			if(score[i] > maxScore && !AGIKnowledge){
				maxScore = score[i];
			}
		}

		if(AGIKnowledge){
			for(i=1; i<NUMBER_OF_TONES; i++){
				if(score[i]){
					submitScore = score[i] - baseScore;
				} else {
					submitScore = 0;
				}
				evaluator.apply("addNotePair", arg);
			}
		}else{
			for(i=1; i<NUMBER_OF_TONES; i++){
			//algebra and other assumptions
			//assumptions being the song starting off with a non-zero score
			//and there is a perfect score attainable with one of the note pairs
				if(score[i] == maxScore){
					submitScore = 1; 
				} else if(score[i] != 0){
					submitScore = maxScore - score[i];
				} else {
					submitScore = 0;
				}
				evaluator.apply("addNotePair", arg);
			}
		}
	}
	/*	}
	}*/
}

//old chord pair actual terminology
void findConsonance(int instrumentType, Note firstNote, Note secondNote){

}

//can take wanted beat 'chord' as element A with 3 others being the rest
//the value associated with multiple notes being played at any give moment 
void findTrackMultiTrackPair(){

}

int songTime2Index(Track track, int time, int tempo){
	int i = 0, j = 0;
	while(i<time*tempo/60){
		i+=track.channel[j].hold_time + track.channel[j].pause_time
		j++;
	}
	return j-1;
}

char * findCurrentNode(){
	Handle arg1 =;
	Handle arg2 =;
	Link lnk(LIST_LINK, arg1, arg2);
	Handle currentNodePair = TLB::getHandle(&lnk);

	SchemEval evaluator(&cogserver().getAtomSpace());
	Handle Answer = evaluator.apply("load-state", currentNodePair);
	char * returnString = Answer[LINKNAMERANGE];
	return returnString;
}
