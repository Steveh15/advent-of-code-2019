#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <map>
#include "IntCodeComputer.h"

namespace Day11 {

	struct Coord {
		int x;
		int y;
	};

	std::ostream& operator<<(std::ostream& out, const Coord& c) {
		out << "{" << c.x << ", " << c.y << "}";
		return out;
	}

	bool operator<(const Coord& lhs, const Coord& rhs) {
		if (lhs.x == rhs.x) return lhs.y < rhs.y;
		else return lhs.x < rhs.x;
		/*if (lhs.x < rhs.x) return true;
		else if (lhs.x == rhs.x) return lhs.y < rhs.y;
		else return false;*/
	};

	class Robot {
	public:
		Coord position;
		// 1 = up, 2 = right, 3 = down, 4 = left;
		int direction;

		Robot() {
			position = { 0,0 };
			direction = 1;
		}

		void turnAndMove(int turn) {
			// turn 0 = left, 1 = right
			if (turn == 0) {
				if (direction == 1) direction = 4;
				else direction -= 1;
			}
			else if (turn == 1) {
				if (direction == 4) direction = 1;
				else direction += 1;
			}

			if (direction == 1) position = { position.x, position.y + 1 };
			else if (direction == 2) position = { position.x + 1, position.y };
			else if (direction == 3) position = { position.x, position.y - 1 };
			else if (direction == 4) position = { position.x - 1, position.y };
		}

	};

	void solution() {

		std::cout << "Day 11 solutions!\n";

		std::string input_str = "3,8,1005,8,328,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,28,1,1003,10,10,3,8,1002,8,-1,10,101,1,10,10,4,10,108,1,8,10,4,10,102,1,8,54,2,1103,6,10,3,8,1002,8,-1,10,101,1,10,10,4,10,108,0,8,10,4,10,101,0,8,80,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,1,8,10,4,10,1002,8,1,102,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1001,8,0,124,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,1,10,4,10,1001,8,0,147,1006,0,35,1,7,3,10,2,106,13,10,2,1104,9,10,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,183,2,7,16,10,2,105,14,10,1,1002,12,10,1006,0,13,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,220,1006,0,78,2,5,3,10,1006,0,92,1006,0,92,3,8,1002,8,-1,10,101,1,10,10,4,10,108,1,8,10,4,10,1001,8,0,255,1006,0,57,2,1001,11,10,1006,0,34,2,1007,18,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,1002,8,1,292,2,109,3,10,1,1103,14,10,2,2,5,10,2,1006,3,10,101,1,9,9,1007,9,997,10,1005,10,15,99,109,650,104,0,104,1,21101,932700762920,0,1,21101,0,345,0,1105,1,449,21102,1,386577306516,1,21102,356,1,0,1106,0,449,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21101,179355975827,0,1,21101,403,0,0,1106,0,449,21102,1,46413220903,1,21102,1,414,0,1106,0,449,3,10,104,0,104,0,3,10,104,0,104,0,21101,988224959252,0,1,21102,1,437,0,1106,0,449,21101,717637968660,0,1,21101,0,448,0,1106,0,449,99,109,2,22101,0,-1,1,21102,40,1,2,21101,480,0,3,21101,470,0,0,1106,0,513,109,-2,2105,1,0,0,1,0,0,1,109,2,3,10,204,-1,1001,475,476,491,4,0,1001,475,1,475,108,4,475,10,1006,10,507,1102,1,0,475,109,-2,2105,1,0,0,109,4,2102,1,-1,512,1207,-3,0,10,1006,10,530,21102,1,0,-3,22102,1,-3,1,22101,0,-2,2,21102,1,1,3,21101,0,549,0,1105,1,554,109,-4,2105,1,0,109,5,1207,-3,1,10,1006,10,577,2207,-4,-2,10,1006,10,577,21202,-4,1,-4,1106,0,645,21202,-4,1,1,21201,-3,-1,2,21202,-2,2,3,21102,1,596,0,1106,0,554,21201,1,0,-4,21101,1,0,-1,2207,-4,-2,10,1006,10,615,21101,0,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,637,21201,-1,0,1,21101,0,637,0,105,1,512,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0";

		std::istringstream is;
		is.str(input_str);

		Robot robot;
		std::map<Coord, int> hull;

		std::vector<__int64> initial_state;
		__int64 t;
		char c;
		while (is >> t) {
			initial_state.push_back(t);
			is >> c;
		}

		IntCodeComputer comp1(initial_state);

		while (!comp1.is_halted) {
			comp1.run(hull[robot.position]);
			// First output : colour to paint
			hull[robot.position] = comp1.getOuput();
			// Second output : 0 turn left, 1 turn right;
			comp1.run(1);
			robot.turnAndMove(comp1.getOuput());
			// Move robot and begin again
		}

		std::cout << "Part 1 solution: " << hull.size() << "\n";

		hull.clear();
		hull[{0, 0}] = 1;
		robot = Robot();

		comp1 = IntCodeComputer(initial_state);

		while (!comp1.is_halted) {
			comp1.run(hull[robot.position]);
			hull[robot.position] = comp1.getOuput();
			comp1.run(1);
			robot.turnAndMove(comp1.getOuput());
		}

		int min_x = std::min_element(hull.begin(), hull.end(), [](std::pair<Coord, int> c1, std::pair<Coord, int> c2) {
			return c1.first.x < c2.first.x;
		})->first.x;
		int max_x = std::max_element(hull.begin(), hull.end(), [](std::pair<Coord, int> c1, std::pair<Coord, int> c2) {
			return c1.first.x < c2.first.x;
		})->first.x;
		int min_y = std::min_element(hull.begin(), hull.end(), [](std::pair<Coord, int> c1, std::pair<Coord, int> c2) {
			return c1.first.y < c2.first.y;
		})->first.y;
		int max_y = std::max_element(hull.begin(), hull.end(), [](std::pair<Coord, int> c1, std::pair<Coord, int> c2) {
			return c1.first.y < c2.first.y;
		})->first.y;

		std::cout << "Part 2 solution: \n";
		for (int y = max_y; y >= min_y; y--) {

			for (int x = min_x; x <= max_x; x++) {
				if (hull[{x, y}] == 1) std::cout << "#";
				else std::cout << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}
};