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
#include <signal.h>
#include "python3_to_cpp_converter.h"
#include "song_structs.h"
#include "sd.h"

Song ai_shell(bool continuing, bool displayText, int * iteration, int score);
void init_AI();
Song start_AI(bool displayText, int * iteration, int score);
void sig_handler(int sig);
int get_diversity(std::vector<Song> song_list, int song_index);

#endif /* AI_SHELL_H_ */
