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

	bool displayText = false, continuing = false;
	int seed = 0, iterations, score = 0;
	struct timeval start_time, end_time;
	Song song;
	
	if (argc == 4) {
		cout << argv[1] << "\n";
		if (strcmp(argv[1],"p") != 0 || strcmp(argv[1],"-p") != 0 || strcmp(argv[1],"print") != 0) {
			displayText = true;
		} else if (strcmp(argv[1],"c") != 0 || strcmp(argv[1],"-c") != 0 || strcmp(argv[1],"continue") != 0)  {
			continuing = true;
		}
		seed = atoi(argv[2]);
		iterations = atoi(argv[3]);
	} else if (argc == 3) {
		seed = atoi(argv[1]);
		iterations = atoi(argv[2]);
	} else {
		cout << "Seed, # iterations\n";
		cin >> seed >> iterations;
	}

	srand(seed);

	// Timing is everything
	gettimeofday(&start_time, NULL);

	for (int i = 0;i < iterations;) {
		song = ai_shell(continuing, displayText, &i, score);
		score = c_shell(song);
		if (displayText)
			printf("Song %d: Score of %d\n", song.song_id, score);
	}
	// Currently the last song is not saved
	//saveLastGen(score);

	gettimeofday(&end_time, NULL);

	cout << "Generation " << iterations << " Complete in " << 
	       (end_time.tv_sec - start_time.tv_sec) << " seconds" << '\n';
}

