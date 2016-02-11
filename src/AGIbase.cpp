#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <opencog/server/CogServer.h>
#include <opencog/server/Factory.h>
#include <opencog/util/Logger.h>
#include <opencog/atomspace/SimpleTruthValue.h>
#include "song_structs.h"
#include "frequencies.h"

int AGImain(){
	int i;
	char * currentNode = findCurrentNode();
	Track currentTrack[INSTRUMENT_TYPES];
	Song currentSong = generateRandomSong(0,127,1);
	Song comparisonSong = generateRandomSong(1,127,1);
	for(i=0 i<INSTRUMENT_TYPES; i++){
		//currentTrack[i] = decoupleTrack(currentSong, comparisonSong, i);
		findNoteCouple(currentSong, comparisonSong, currentNode);
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
Track generateRandomTrack(int ID, int volume){
	Track newTrack;
	Note newNote;
	int i = 0, j = 0;
	newTrack.instrument_id = INSTRUMENT_NUMBER*(ID+rand())/INSTRUMENT_TYPES%INSTRUMENT_NUMBER;
	while(j<MAX_NOTES){
		newNote.pause_time = 16*rand(); 
		newNote.hold_time = 16*rand(); 
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
	return newTrack;
}

Track decoupleTrack(Song importantSong, Song testSong, int instrumentIndex, char* currentNode){
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

void findNotePair(Song importantSong, Song testSong, char* currentNode){
	Note subTrack1[2], subTrack2[MAX_NOTES],subTrack3[MAX_NOTES], subTrack4[MAX_NOTES];
	subTrack1[0] = importantSong.tunes[0].channel[0];
	subTrack1[1] = importantSong.tunes[0].channel[1];
	//query the AtomSpace if it knows about subTrack1
	

}

//can take wanted beat 'chord' as element A with 3 others being the rest 
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
	Handle Answer = evaluator.apply("name", currentNodePair);
	char * returnString = Answer[LINKNAMERANGE];
	return returnString;
}
