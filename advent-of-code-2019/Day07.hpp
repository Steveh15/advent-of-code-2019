#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <queue>

namespace Day7 {

	int nthDigit(const int& i, const int& n) {
		return (i % (int)pow(10, n)) / (int)pow(10, n - 1);
	}

	class Computer {

	private:
		std::vector<int> states;
		int i;
		std::queue<int> input_queue;
		bool used_phase;
		std::queue<int> output_queue;

	public:
		bool is_halted;
		Computer(std::vector<int> _states, int _phase) : states(_states) {
			i = 0;
			is_halted = false;
			input_queue.push(_phase);
			used_phase = false;
		};

		int getOuput() {
			return  output_queue.back();
		}

		void run(int input) {
		
			input_queue.push(input);

			while (!is_halted) {
				int instruction = states[i];

				int opcode = 10 * nthDigit(instruction, 2) + nthDigit(instruction, 1);
				int p1 = nthDigit(instruction, 3);
				int p2 = nthDigit(instruction, 4);

				if (opcode == 3) {
					states[states[i + 1]] = !used_phase ? input_queue.front() : input_queue.back();
					used_phase = true;
					i += 2;
				}
				else if (opcode == 4) {
					output_queue.push(states[states[i + 1]]);
					i += 2;
					return; // Halt!
				}
				else if (opcode == 99) is_halted = true;
				else {
					int val1 = p1 == 0 ? states[states[i + 1]] : states[i + 1];
					int val2 = p2 == 0 ? states[states[i + 2]] : states[i + 2];

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
			return;
		}
	};

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
		std::vector<int> phase = {0,1,2,3,4};
		std::sort(phase.begin(), phase.end());
		do {
			Computer amp1(initial_state, phase[0]);
			Computer amp2(initial_state, phase[1]);
			Computer amp3(initial_state, phase[2]);
			Computer amp4(initial_state, phase[3]);
			Computer amp5(initial_state, phase[4]);

			amp1.run(0);
			amp2.run(amp1.getOuput());
			amp3.run(amp2.getOuput());
			amp4.run(amp3.getOuput());
			amp5.run(amp4.getOuput());
			phase_map[phase] = amp5.getOuput();
		} while (std::next_permutation(phase.begin(), phase.end()));

		auto max = std::max_element(phase_map.begin(), phase_map.end(), [](std::pair < std::vector<int>, int> a, std::pair < std::vector<int>, int> b) {
			return a.second < b.second;
		});
		std::cout << "Part 1 solution: " << max->second << "\n";

		phase_map.clear();
		phase = { 5,6,7,8,9};
		std::sort(phase.begin(), phase.end());

		do {
			Computer amp1(initial_state, phase[0]);
			Computer amp2(initial_state, phase[1]);
			Computer amp3(initial_state, phase[2]);
			Computer amp4(initial_state, phase[3]);
			Computer amp5(initial_state, phase[4]);
			amp1.run(0);
			amp2.run(amp1.getOuput());
			amp3.run(amp2.getOuput());
			amp4.run(amp3.getOuput());
			amp5.run(amp4.getOuput());
			while (!amp5.is_halted) {
				amp1.run(amp5.getOuput());
				amp2.run(amp1.getOuput());
				amp3.run(amp2.getOuput());
				amp4.run(amp3.getOuput());
				amp5.run(amp4.getOuput());
			}
			phase_map[phase] = amp5.getOuput();
		} while (std::next_permutation(phase.begin(), phase.end()));

		auto max2 = std::max_element(phase_map.begin(), phase_map.end(), [](std::pair < std::vector<int>, int> a, std::pair < std::vector<int>, int> b) {
			return a.second < b.second;
		});
		std::cout << "Part 2 solution: " << max2->second << "\n";
		std::cout << "\n";


	}
};