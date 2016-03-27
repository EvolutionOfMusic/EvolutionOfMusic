/* make_wav.c
 * Creates a WAV file from an array of ints.
 * Output is monophonic, signed 16-bit samples
 * copyright
 * Fri Jun 18 16:36:23 PDT 2010 Kevin Karplus
 * Creative Commons license Attribution-NonCommercial
 *  http://creativecommons.org/licenses/by-nc/3.0/
 */

#ifndef make_wav_h
#define make_wav_h
 
#include <stdio.h>
#include <assert.h>
 
void write_little_endian(unsigned int word, int num_bytes, FILE *wav_file);
void write_wav(char * filename, unsigned long num_samples, float * data, int s_rate);

#endif
