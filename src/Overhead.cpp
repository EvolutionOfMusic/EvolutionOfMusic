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

	int seed, iterations, score, total_time;
	time_t start_time, end_time;
	Song song;

	cin >> seed >> iterations;

	srand(seed);

	// Timing is everything
	start_time = time(0);

	song = ai_shell(0);
	for (int i = 0;i < iterations;i++) {
		score = c_shell(song);
		song = ai_shell(iterations-i, score);
	}

	end_time = time(0);
	total_time = difftime(start_time, end_time);

	cout << "Generation " << iterations << " Complete in " << total_time << " seconds" << '\n';
}

