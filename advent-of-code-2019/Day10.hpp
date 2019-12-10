#pragma once
#include <math.h>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <corecrt_math_defines.h>




namespace Day10 {

	void solution() {


		std::cout << "Day 10 solutions!\n";
		std::vector<std::string>  input;

		// Who needs a file reader?
		input.push_back("##.##..#.####...#.#.####");
		input.push_back("##.###..##.#######..##..");
		input.push_back("..######.###.#.##.######");
		input.push_back(".#######.####.##.#.###.#");
		input.push_back("..#...##.#.....#####..##");
		input.push_back("#..###.#...#..###.#..#..");
		input.push_back("###..#.##.####.#..##..##");
		input.push_back(".##.##....###.#..#....#.");
		input.push_back("########..#####..#######");
		input.push_back("##..#..##.#..##.#.#.#..#");
		input.push_back("##.#.##.######.#####....");
		input.push_back("###.##...#.##...#.######");
		input.push_back("###...##.####..##..#####");
		input.push_back("##.#...#.#.....######.##");
		input.push_back(".#...####..####.##...##.");
		input.push_back("#.#########..###..#.####");
		input.push_back("#.##..###.#.######.#####");
		input.push_back("##..##.##...####.#...##.");
		input.push_back("###...###.##.####.#.##..");
		input.push_back("####.#.....###..#.####.#");
		input.push_back("##.####..##.#.##..##.#.#");
		input.push_back("#####..#...####..##..#.#");
		input.push_back(".##.##.##...###.##...###");
		input.push_back("..###.########.#.###..#.");

		std::map<int, int> asteroid_count;

		// Assuming a square map
		int dim = input.size();

		for (int y = 0; y < dim; y++) {
			for (int x = 0; x < dim; x++) {

				std::set<double> angle_set;
				if (input[y][x] == '#') {

					for (int y2 = 0; y2 < dim; y2++) {
						for (int x2 = 0; x2 < dim; x2++) {
							if (input[y2][x2] == '#' and !(y2 == y and x2 == x)) {
								//Find angle between two asteroids
								angle_set.insert(atan2(y2 - y, x2 - x));
							}
						}
					}
					asteroid_count[x * 100 + y] = angle_set.size();
				}
			}
		}

		auto max = std::max_element(asteroid_count.begin(), asteroid_count.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
			return a.second < b.second;
		});

		int x = (max->first) / 100;
		int y = (max->first) % 100;
		std::cout << "Part 1 solution : " << max->second << " (at " << x << ", " << y << ")\n";




		// Create angle map (map of angles on to vector of asteroids that fall on that angle)
		std::map<double, std::vector<int>> angle_map;
		for (int y2 = 0; y2 < dim; y2++) {
			for (int x2 = 0; x2 < dim; x2++) {
				if (input[y2][x2] == '#' and !(y2 == y and x2 == x)) {
					// Angle adjusted so that it runs from 0->2PI clockwise
					double angle = atan2(x - x2, y - y2);
					angle = angle <= 0 ? abs(angle) : 2 * M_PI - angle;
					angle_map[angle].push_back(x2 * 100 + y2);
				}
			}
		}


		for (auto a : angle_map) {
			// Sort the asteroids according to which is closest, furtherest away first
			std::sort(a.second.begin(), a.second.end(), [x, y](int a, int b) {
				double a_dist, b_dist;
				a_dist = sqrt(pow(a / 100 - x, 2) + pow(a % 100 - y, 2));
				b_dist = sqrt(pow(b / 100 - x, 2) + pow(b % 100 - y, 2));
				return b_dist < a_dist;
			});
		}


		// Start destroying asteroids!
		std::vector<int> destroyed_asteroids;
		while (destroyed_asteroids.size() < 200) {
			for (auto a : angle_map) {
				if (a.second.size() > 0) {
					destroyed_asteroids.push_back(a.second.back());
					a.second.pop_back();
				}
			}

		}

		std::cout << "Part 2 solution : " << destroyed_asteroids[199] << "\n";

		std::cout << "\n";
	}
};

