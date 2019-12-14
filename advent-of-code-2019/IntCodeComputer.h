#pragma once
#include <vector>
#include <queue>


class IntCodeComputer
{



private:
	std::vector<__int64> states;
	__int64 i, rel_base;
	std::queue<__int64> input_queue;
	std::queue<__int64> output_queue;


	__int64 nthDigit(const __int64& i, const __int64& n) {
		return (i % (__int64)pow(10, n)) / (__int64)pow(10, n - 1);
	}

public:
	bool is_halted;
	IntCodeComputer(std::vector<__int64> _states) : states(_states) {
		i = 0;
		is_halted = false;
		rel_base = 0;
	};

	__int64 getOuput() {
		return  output_queue.back();
	}

	__int64 getState(__int64 index) {
		if (index > (__int64)(states.size() - 1))
			states.resize(index + 1, 0);
		return states[index];
	}

	void setState(__int64 pnum, __int64 value) {
		__int64 mode = nthDigit(getState(i), 2 + pnum), temp_index = 0;
		if (mode == 0) temp_index = getState(i + pnum);
		else if (mode == 2) temp_index = rel_base + getState(i + pnum);

		if (temp_index > (__int64)(states.size() - 1))
			states.resize(temp_index + 1, 0);
		if (temp_index >= 0) states[temp_index] = value;
	}

	__int64 getParam(__int64 pnum) {
		__int64 mode = nthDigit(getState(i), 2 + pnum), temp_index = 0;
		if (mode == 0) temp_index = getState(i + pnum);
		else if (mode == 1) temp_index = i + pnum;
		else if (mode == 2) temp_index = rel_base + getState(i + pnum);
		return getState(temp_index);
	}

	void run(__int64 input) {

		input_queue.push(input);

		while (!is_halted) {
			__int64 instruction = states[i];

			__int64 opcode = 10 * nthDigit(instruction, 2) + nthDigit(instruction, 1);

			if (opcode == 1) {
				setState(3, getParam(1) + getParam(2));
				i += 4;
			}
			else if (opcode == 2) {
				setState(3, getParam(1) * getParam(2));
				i += 4;
			}
			if (opcode == 3) {
				setState(1, input_queue.back());
				i += 2;
			}
			else if (opcode == 4) {
				output_queue.push(getParam(1));
				i += 2;
				return; // Halt!
			}
			else if (opcode == 5)
				i = getParam(1) != 0 ? getParam(2) : i + 3;
			else if (opcode == 6)
				i = getParam(1) == 0 ? getParam(2) : i + 3;
			else if (opcode == 7) {
				setState(3, getParam(1) < getParam(2) ? 1 : 0);
				i += 4;
			}
			else if (opcode == 8) {
				setState(3, getParam(1) == getParam(2) ? 1 : 0);
				i += 4;
			}
			else if (opcode == 9) {
				rel_base += getParam(1);
				i += 2;
			}
			else if (opcode == 99) is_halted = true;
		}
		return;
	}

};

