#pragma once



namespace Day2 {



	int computer(std::vector<int> input) {
		int i = 0;
		bool error = false;
		while (input[i] != 99 || error) {

			if (input[i] == 1) {
				input[input[i + 3]] = input[input[i + 1]] + input[input[i + 2]];
			}
			else if (input[i] == 2) {
				input[input[i + 3]] = input[input[i + 1]] * input[input[i + 2]];
			}
			else if (input[i] != 99) {
				std::cout << "Fatal error, halt program immiediately";
				error = true;
			}
			i += 4;
		}
		return input[0];
	};


	void solution() {

		std::cout << "Day 2 solutions!\n";

		std::ifstream is("../inputs/day02.txt");

		if (!is.is_open()) {
			throw std::runtime_error("Could not open puzzle input file");
		}

		std::vector<int> initial_state;
		int t;
		char c;
		while (is >> t) {
			initial_state.push_back(t);
			is >> c;
		}


		std::vector<int> input = initial_state;
		input[1] = 12;
		input[2] = 2;
		int result = computer(input);

		std::cout << "Part one solution : " << result << "\n";

		int noun = 0;
		int verb = -1;

		while (result != 19690720) {

			verb += 1;
			if (verb == 100) {
				verb = 0;
				noun += 1;
			}
			if (noun == 100) {
				std::cout << "No solution found\n";
				break;
			}

			input = initial_state;
			input[1] = noun;
			input[2] = verb;
			result = computer(input);
		}

		std::cout << "Part two solution : " << 100 * noun + verb << "\n";
		std::cout << "\n";
	}

};