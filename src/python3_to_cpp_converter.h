/* 
 * File:   python3_to_cpp_converter.h
 * Author: Stephen Andersen
 *
 * Created on February 24, 2016, 10:20 AM
 */

#ifndef PYTHON_CONV_H_
#define PYTHON_CONV_H_

#include <cstdlib>
#include <fstream> // ifstream, ofstream
#include <iostream>
#include <list>
#include "song_structs.h"

std::list<Song> parse_song(std::ifstream &file);

#endif /* PYTHON_CONV_H_ */
