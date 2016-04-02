#include "main.h"

int main(int argc, char **argv) {
	if (argc != 2) return 0;
	std::ifstream file(argv[1]);
	printf("Found file %s\n", argv[1]);
	//std::ifstream file("../../main_py_output");
	std::list<Song> song_list = parse_song(file);

	printf("Got %i song(s) from %s\n", song_list.size(), argv[1]);
	for(std::list<Song>::iterator it = song_list.begin();
	        it != song_list.end();it++)
	    C2Wav((*it));
}
