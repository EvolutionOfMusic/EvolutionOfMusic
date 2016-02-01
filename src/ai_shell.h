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
#include "song_structs.h"

Song ai_shell(int score);
void start_AI(Song *output, int score);

#endif /* AI_SHELL_H_ */
