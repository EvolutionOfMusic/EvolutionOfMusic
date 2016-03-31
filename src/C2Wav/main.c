#include "main.h"

int main(int argc, char **argv) {
	if (argc != 2) return 0;
	std::ifstream file(argv[1]);
	printf("Found file %s\n", argv[1]);
	//std::ifstream file("../../main_py_output");
	std::list<Song> song_list = parse_song(file);

	Song song;
	song.song_id = 8888888;
	song.track_num = 2;
	song.tunes[0].track_length = 4;
	song.tunes[0].channel[0].tone = 56;
	song.tunes[0].channel[0].hold_time = 4;
	song.tunes[0].channel[0].pause_time = 0;

	song.tunes[0].channel[1].tone = 0;
	song.tunes[0].channel[1].hold_time = 4;
	song.tunes[0].channel[1].pause_time = 0;
	
	song.tunes[0].channel[2].tone = 0;
	song.tunes[0].channel[2].hold_time = 4;
	song.tunes[0].channel[2].pause_time = 0;
	
	song.tunes[0].channel[3].tone = 56;
	song.tunes[0].channel[3].hold_time = 4;
	song.tunes[0].channel[3].pause_time = 0;
	
	song.tunes[1].track_length = 4;
	song.tunes[1].channel[0].tone = 0;
	song.tunes[1].channel[0].hold_time = 4;
	song.tunes[1].channel[0].pause_time = 0;

	song.tunes[1].channel[1].tone = 68;
	song.tunes[1].channel[1].hold_time = 4;
	song.tunes[1].channel[1].pause_time = 0;

	song.tunes[1].channel[2].tone = 0;
	song.tunes[1].channel[2].hold_time = 4;
	song.tunes[1].channel[2].pause_time = 0;

	song.tunes[1].channel[3].tone = 68;
	song.tunes[1].channel[3].hold_time = 4;
	song.tunes[1].channel[3].pause_time = 0;

	song_list.push_back(song);

	//printf("%i %i %i\n", song.tunes[0].channel[0].tone, song.tunes[0].channel[0].hold_time, song.tunes[0].channel[0].pause_time);

	printf("Got %i song(s) from %s\n", song_list.size(), argv[1]);
	//for(std::list<Song>::iterator it = song_list.begin();
	  //      it != song_list.end();it++)
	  //  C2Wav((*it));
	C2Wav(song);
}
