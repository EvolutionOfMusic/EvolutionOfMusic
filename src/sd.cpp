/*
 * sd.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: Stephen
 */


#include "sd.h"

const int port_number = 1111;

void error(const char *msg){
	perror(msg);
}

void init_sd() {
	ofstream toSD;
	toSD.open("music");
	toSD.close();
}

void set_sd(vector<Song> song_list) {
	ofstream toSD;
	toSD.open("music");
	for ()
	toSD <<  <<\n";
	toSD.close();
}
