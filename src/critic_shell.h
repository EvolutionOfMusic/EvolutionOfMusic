/*
 * critic_shell.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#ifndef CRITIC_SHELL_H_
#define CRITIC_SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "frequencies.h"
#include "song_structs.h"

long long c_shell(Song song);
long long supervisor(Song song);
int manual_override(Song song);
Note getNoteAtBeat(Track track, int beat);

#endif /* CRITIC_SHELL_H_ */
