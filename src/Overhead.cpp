/*
 * Overhead.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Stephen
 */
// Unit Tests
//#include <boost/test/minimal.hpp>
//#define BOOST_TEST_MODULE MyTest
//#include <boost/test/unit_test.hpp>
//#include <gtest/gtest.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ethernet.h"
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
	start_time = time(0);

	song = ai_shell(0);
	for (int i = 0;i < iterations;i++) {
		score = c_shell(song);
		song = ai_shell(score);

		if (play_music_switch())
			play_music(song);
	}

	end_time = time(0);
	total_time = difftime(start_time, end_time);

	cout << "Generation " << iterations << " Complete in " << total_time << " seconds" << '\n';
}

bool play_music_switch() {
		info status = get_ethernet();
		return status.play_music;
}

/*int test_main(int, char *[]) {
	BOOST_CHECK(true);
	return 0;
}*/
