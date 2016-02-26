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

Song ai_shell(int score);
Song start_AI(int score);
void sig_handler(int sig);

#endif /* AI_SHELL_H_ */
