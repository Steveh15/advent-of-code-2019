#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace Day08 {

	void solution() {

		std::cout << "Day 8 solutions!\n";
		std::string input = get_lines("day08.txt")[0];
		std::vector<std::vector<int>> layers, layers_sorted;;

		for (int i = 0; i < input.size(); i++) {
			if (i % 150 == 0) layers.push_back({});
			layers.back().push_back(input[i] - '0');
		}

		layers_sorted = layers;
		std::sort(layers_sorted.begin(), layers_sorted.end(), [](std::vector<int> a, std::vector<int> b) {
			return std::count(a.begin(), a.end(), 0) < std::count(b.begin(), b.end(), 0);
		});

		std::cout << "Part 1 solution : " << std::count(layers_sorted[0].begin(), layers_sorted[0].end(), 1) * std::count(layers_sorted[0].begin(), layers_sorted[0].end(), 2) << "\n";

		std::cout << "Part 2 solution : " << "\n";
		for (int i = 0; i < 150; i++) {
			int pixel = 2;
			for (int j = 0; j < layers.size(); j++) {
				if (layers[j][i] != 2) {
					pixel = layers[j][i];
					break;
				}
			}
			if (i % 25 == 0) std::cout << "\n";
			if (pixel == 1) std::cout << '#';
			else std::cout << ' ';
		}


		std::cout << "\n";
	}
};
