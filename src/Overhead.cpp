#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "synthesizer.h"
#include "critic_shell.h"
#include "ai_shell.h"
//#include "song_structs.h"


bool play_music_switch();

int main() {
	using namespace std;
	// cin & cout

	int seed, iterations, score, total_time;
	time_t start_time, end_time;
	Song song;

	cin >> seed >> iterations;

	srand(seed);

	// Timing is everything
	start_time = clock();

	song = ai_shell(0);
	for (int i = 0;i < iterations;i++) {
		score = c_shell(song);
		song = ai_shell(score);

		if (play_music_switch())
			play_music(song);
	}

	end_time = clock();
	total_time = difftime(start_time, end_time);

	cout << "Music Complete in :" << total_time << "seconds" << '\n';
}

bool play_music_switch() {
	//TODO
	return false;
}
