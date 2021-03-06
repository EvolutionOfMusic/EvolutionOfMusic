/*
 * canon_in_d_test.cpp
 *
 *  Created on: March 28, 2016
 *      Author: Lee
 */
#include "python3_to_cpp_converter.h"
#include "critic_shell.h"
#include "song_structs.h"
#include "frequencies.h"
#include <fstream>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc != 2) return 1;
  std::list <Song> cannon;
  long long score;
  std::ifstream ifs(argv[1], std::ifstream::in);

  cannon = parse_song(ifs);
  for (std::list<Song>::const_iterator iterator = cannon.begin();iterator != cannon.end();iterator++) {
    score = c_shell(*iterator); 
    std::cout << "The score is: " << score << std::endl;
  }
  ifs.close();

  return 0;
}
