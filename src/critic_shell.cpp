/*
 * critic_shell.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Stephen
 */

#include "critic_shell.h"
#include <fstream>
#include <iostream>

const int NOTES_PER_OCTAVE = 12;
const int BEATS_PER_MEASURE = 16;
const int C6_INDEX = 5 * NOTES_PER_OCTAVE + 1;
const int C3_INDEX = 4 * NOTES_PER_OCTAVE + 1;

/* A Song holds Tracks; A Track holds Notes
 * Consonance is good; Dissonance is bad
 * https://en.wikipedia.org/wiki/Consonance_and_dissonance
 * https://musicmasterworks.com/WhereMathMeetsMusic.html
 * https://en.wikipedia.org/wiki/Pythagorean_tuning
 * http://hyperphysics.phy-astr.gsu.edu/hbase/music/mussca.html
 * - Also used for transitions
 */
const int CONSONANCE = 600;
const int CONSONANCE_RANGE = 8;
/* Rhythm
 * - Being on the same beat is good
 * - 4/4 Time is good
 */
const int PERFECT_TIME = 1000;
const int FOURFOUR_TIME = 20000;
const int MORE_RESTS = 10;
/* Length
 * - Slower notes for faster songs
