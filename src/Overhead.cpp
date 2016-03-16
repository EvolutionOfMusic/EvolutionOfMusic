/*
 * Overhead.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Stephen
 */

#include "Overhead.h"

int main(int argc, char *argv[]) {
	using namespace std;
	// cin & cout

	int seed, iterations, score = 0, temp = 0;
	struct timeval start_time, end_time;
	Song song;

	if (argc == 3) {
		seed = atoi(argv[0]);
		iterations = atoi(argv[1]);
	} else {
		cout << "Seed, # iterations\n";
		cin >> seed >> iterations;
	}

	srand(seed);

	// Timing is everything
	gettimeofday(&start_time, NULL);

	for (int i = 0;i < iterations;) {
		song = ai_shell(&i, score);
		score = c_shell(song);
		printf("Score of %d for Song %d\n", score, song.song_id);
	}
	// Currently the last song is not saved
	//saveLastGen(score);

	gettimeofday(&end_time, NULL);

	cout << "Generation " << iterations << " Complete in " << 
	       (end_time.tv_sec - start_time.tv_sec) << " seconds" << '\n';
}

