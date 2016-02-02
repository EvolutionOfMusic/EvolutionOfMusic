/*
 * ethernet.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: Stephen
 */


#include "ethernet.h"

info get_ethernet() {
	info status;

	// TODO Read Ethernet
	status.manual_override = false;
	status.play_music = false;

	return status;
}

void play_music(Song song) {
	//TODO send song via Ethernet to DE2
}
