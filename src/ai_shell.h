/*
 * ai_shell.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#ifndef AI_SHELL_H_
#define AI_SHELL_H_

// rand
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "python3_to_cpp_converter.h"
#include "song_structs.h"

Song ai_shell(bool continuing, bool displayText, int * iteration, long long score);
void init_AI();
Song start_AI(bool displayText, int * iteration, long long score);
//void sig_handler(int sig);
int get_diversity(std::list<Song> song_list, std::list<Song>::iterator current);//int song_index);

#endif /* AI_SHELL_H_ */
