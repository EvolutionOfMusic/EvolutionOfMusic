#include "main.h"
#include <string.h>

int main(int argc, char **argv) {
	if (argc < 2) return 0;

	std::list<Song> song_list;
	int type = 0;
	
	if (argc == 3 && strcmp(argv[1], "GUITAR") == 0) {
		type = 10;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "WOODBLOCK") == 0) {
		type = 9;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "HARP") == 0) {
		type = 8;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "ACCORDIAN") == 0) {
		type = 7;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "BASSOON") == 0) {
		type = 6;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "ORGAN") == 0) {
		type = 5;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "BELL") == 0) {
		type = 4;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "BRASS") == 0) {
		type = 3;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "FM") == 0) {
		type = 1;
		std::ifstream file(argv[2]);
		printf("Found file %s\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else if (argc == 3 && strcmp(argv[1], "AM") == 0) {
		type = 2;
		std::ifstream file(argv[2]);
		printf("Found file %s2\n", argv[2]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[2]);
	} else {
		std::ifstream file(argv[1]);
		printf("Found file %s\n", argv[1]);
		//std::ifstream file("../../main_py_output");
		song_list = parse_song(file);
		printf("Got %lu song(s) from %s\n", song_list.size(), argv[1]);
	}

	for(std::list<Song>::iterator it = song_list.begin();
	        it != song_list.end();it++)
	    C2Wav(type, (*it));
}
