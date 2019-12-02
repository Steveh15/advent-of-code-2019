#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

#include "get_input.hpp"


namespace Day1 {


	void solution() {



		std::cout << "Day 1 solutions:\n";
		std::vector<int> input = get_input<int>("day01.txt");

		int p1 = std::accumulate(input.begin(), input.end(), 0, [](int a, int b) {
			return  a + b/3-2;
		});

		std::cout << "Part one solution : " << p1 << "\n";


		int p2 = std::accumulate(input.begin(), input.end(), 0, [](int a, int b) {
			int fuel = 0;
			int fn = b / 3 - 2;
			while (fn > 0) {
				fuel += fn;
				fn = fn / 3 - 2;
			}
			return a + fuel;
		});


		std::cout << "Part two solution : " << p2 << "\n";


	};


}