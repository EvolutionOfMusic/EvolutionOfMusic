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

	song = ai_shell(&temp, 0);
	for (int i = 0;i < iterations;) {
                if (temp != i) {
		  printf("ITERATION %d\n", i);
		  temp = i;
		}
		score = c_shell(song);
		printf("Score of %d\n", score);
		song = ai_shell(&i, score);
		printf("Song track_num in Overhead = %hd\n", song.track_num);
	}

	gettimeofday(&end_time, NULL);

	cout << "Generation " << iterations << " Complete in " << 
	       (end_time.tv_sec - start_time.tv_sec) << "." << 
	       (end_time.tv_usec - start_time.tv_usec) << " seconds" << '\n';
}

