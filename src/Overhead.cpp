/*
 * Overhead.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Stephen
 */

#include "Overhead.h"

int main() {
	using namespace std;
	// cin & cout

	int seed, iterations, score;
	int temp = 0;
	struct timeval start_time, end_time;
	Song song;

	cin >> seed >> iterations;

	srand(seed);

	// Timing is everything
	gettimeofday(&start_time, NULL);

	for (int i = 0;i < iterations;) {
		if (temp != i) {
		  printf("ITERATION %d\n", i);
		  temp = i;
		}
		if (i == 0) {
			song = ai_shell(&temp, temp);
		} else {
			song = ai_shell(&i, score);
		}
		score = c_shell(song);
		printf("Score of %d for Song %d\n", score, song.song_id);
	}
	// Currently the last song is not saved
	//saveLastGen(score);

	gettimeofday(&end_time, NULL);

	cout << "Generation " << iterations << " Complete in " << 
	       (end_time.tv_sec - start_time.tv_sec) << " seconds" << '\n';
}

