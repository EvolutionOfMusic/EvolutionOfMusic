#include "python3_to_cpp_converter.h"
#include "critic_shell.h"
#include "song_structs.h"
#include "frequencies.h"
#include <fstream>
#include <iostream>

int main() {
  std::vector <Song> cannon;
  int score;
  std::ifstream ifs("openingToCanonInD", std::ifstream::in);

  cannon = parse_song(ifs);
  score = c_shell(cannon.at(0)); 

  std::cout << "The score is: " << score << std::endl;
  ifs.close();

  return 0;
}
