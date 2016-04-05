/*
 * sd.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#ifndef SD_H_
#define SD_H_

#include <list>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "song_structs.h"
using namespace std;

void error(const char* msg);
void set_sd(std::list<Song> song_list);

#endif /* SD_H_ */
