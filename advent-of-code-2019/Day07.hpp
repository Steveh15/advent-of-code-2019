#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>;
#include <sstream>

namespace Day7 {


	int nthDigit(const int& i, const int& n) {
		return (i % (int)pow(10, n)) / (int)pow(10, n - 1);
	}

	int computer(int input1, int input2, std::vector<int> states) {
		int i, instruction, opcode, p1, p2, p3, val1, val2;
		opcode = 0;
		i = 0;
		int output = 0;
		bool first_input = true;

		while (opcode != 99) {
			instruction = states[i];

			opcode = 10 * nthDigit(instruction, 2) + nthDigit(instruction, 1);
			p1 = nthDigit(instruction, 3);
			p2 = nthDigit(instruction, 4);


			if (opcode == 3) {
				states[states[i + 1]] = first_input ? input1 : input2;
				first_input = false;
				i += 2;
			}
			else if (opcode == 4) {
				output = states[states[i + 1]];
				i += 2;
			}
			else if (opcode == 99);
			else {
				val1 = p1 == 0 ? states[states[i + 1]] : states[i + 1];
				val2 = p2 == 0 ? states[states[i + 2]] : states[i + 2];

				if (opcode == 1) {
					states[states[i + 3]] = val1 + val2;
					i += 4;
				}
				else if (opcode == 2) {
					states[states[i + 3]] = val1 * val2;
					i += 4;
				}
				else if (opcode == 5)
					i = val1 != 0 ? val2 : i + 3;
				else if (opcode == 6)
					i = val1 == 0 ? val2 : i + 3;
				else if (opcode == 7) {
					states[states[i + 3]] = val1 < val2 ? 1 : 0;
					i += 4;
				}
				else if (opcode == 8) {
					states[states[i + 3]] = val1 == val2 ? 1 : 0;
					i += 4;
				}
			}

		}
		return output;
	}





	void solution() {


		std::cout << "Day 7 solutions!\n";

		std::string input_str = "3,8,1001,8,10,8,105,1,0,0,21,34,59,76,101,114,195,276,357,438,99999,3,9,1001,9,4,9,1002,9,4,9,4,9,99,3,9,102,4,9,9,101,2,9,9,102,4,9,9,1001,9,3,9,102,2,9,9,4,9,99,3,9,101,4,9,9,102,5,9,9,101,5,9,9,4,9,99,3,9,102,2,9,9,1001,9,4,9,102,4,9,9,1001,9,4,9,1002,9,3,9,4,9,99,3,9,101,2,9,9,1002,9,3,9,4,9,99,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,99,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,99";
		std::istringstream is;
		is.str(input_str);

		std::vector<int> initial_state;
		int t;
		char c;
		while (is >> t) {
			initial_state.push_back(t);
			is >> c;
		}

		std::map<std::vector<int>, int> phase_map;
		std::vector<int> phase = { 0,1,2,3,4};
		std::sort(phase.begin(), phase.end());
		int res1, res2, res3, res4, res5;
		do {
			res1 = computer(phase[0], 0, initial_state);
			res2 = computer(phase[1], res1, initial_state);
			res3 = computer(phase[2], res2, initial_state);
			res4 = computer(phase[3], res3, initial_state);
			res5 = computer(phase[4], res4, initial_state);
			phase_map[phase] = res5;
		} while (std::next_permutation(phase.begin(), phase.end()));

		auto max = std::max_element(phase_map.begin(), phase_map.end(), [](std::pair < std::vector<int>, int> a, std::pair < std::vector<int>, int> b) {
			return a.second < b.second;
		});
		std::cout << "Part 1 solution: " << max->second << "\n";


		// No part 2 solution yet, need to learn threads first
		// 

		std::cout << "\n";
	}
};