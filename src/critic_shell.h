/*
 * critic_shell.h
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#ifndef CRITIC_SHELL_H_
#define CRITIC_SHELL_H_

#include <math.h>
#include "ethernet.h"
#include "frequencies.h"
#include "song_structs.h"

int c_shell(Song song);
bool override_switch();
int supervisor(Song song);
int manual_override(Song song);

#endif /* CRITIC_SHELL_H_ */
