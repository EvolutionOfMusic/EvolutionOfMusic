/*
 * ethernet.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

// TODO: SOCKETS YET AGAIN!
// http://www.linuxhowtos.org/C_C++/socket.htm
#include <sys/types.h>
//#include <sys/socket.h>
#include "song_structs.h"

struct info {
	bool play_music,
		 manual_override;
};

void play_music(Song song);
info get_ethernet();

#endif /* ETHERNET_H_ */
