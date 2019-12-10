#pragma once


#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <regex>
#include "get_input.hpp"



namespace Day3 {

	struct Coord {
		int x; 
		int y;
	};

	std::istream& operator>>(std::istream& is, Coord& c) {
		return is;
	}

	std::ostream& operator<<(std::ostream& out, Coord& c) {
		out << "[" << c.x << "< " << c.y << "]";
		return out;
	}

	bool operator<(const Coord& lhs, const Coord& rhs) {
		return (abs(lhs.x) + abs(lhs.y)) < (abs(rhs.x) + abs(rhs.y));
	}

	bool operator==(const Coord& lhs, const Coord& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	void increaseX(Coord & c) {c.x += 1;}
	void decreaseX(Coord& c) { c.x -= 1; }
	void increaseY(Coord& c) { c.y += 1; }
	void decreaseY(Coord& c) { c.y -= 1; }


	void solution();

};



namespace std {
	template <>
	struct hash<Day3::Coord>
	{
		std::size_t operator()(const Day3::Coord& k) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()(k.x)
				^ (hash<int>()(k.y) << 1)) >> 1);
		}
	};

}




void Day3::solution(){

	std::cout << "Day 3 solutions!\n";

	std::vector<std::string> input_lines = get_lines("day03.txt");
	std::istringstream stream1;

	char c, comma;
	int m;

	std::unordered_map<Coord, std::pair<int,int>> wire_map_steps;
	Coord current_pos = { 0, 0 };
	int steps = 0;
	void (*wireStep)(Coord&) = &increaseX;

	stream1.str(input_lines[0]);

	while (stream1.good()) {
		stream1 >> c >> m >> comma;

		if (c == 'R')
			wireStep = &increaseX;
		else if (c == 'L')
			wireStep = &decreaseX;
		else if (c == 'U') 
			wireStep = &increaseY;
		else if (c == 'D') 
			wireStep = &decreaseY;

		for (int i = 1; i <= m; i++) {
			steps += 1;
			wireStep(current_pos);

			if (wire_map_steps[current_pos].first == 0) 
				wire_map_steps[current_pos].first = steps;
		}
	}

	stream1.clear();
	stream1.str(input_lines[1]);
	current_pos = { 0, 0 };
	steps = 0;

	while (stream1.good()) {
		stream1 >> c >> m >> comma;

		if (c == 'R')
			wireStep = &increaseX;
		else if (c == 'L')
			wireStep = &decreaseX;
		else if (c == 'U')
			wireStep = &increaseY;
		else if (c == 'D')
			wireStep = &decreaseY;

		for (int i = 1; i <= m; i++) {
			steps += 1;
			wireStep(current_pos);

			if (wire_map_steps[current_pos].second == 0)
				wire_map_steps[current_pos].second = steps;
		}
	}



	auto it1 = std::min_element(wire_map_steps.begin(), wire_map_steps.end(), [](std::pair<Coord, std::pair<int, int>> a, std::pair<Coord, std::pair<int, int>> b) {
		int ls1, ls2, rs1, rs2;
		ls1 = a.second.first;
		ls2 = a.second.second;
		rs1 = b.second.first;
		rs2 = b.second.second;

		if ((ls1 == 0 || ls2 == 0) and (rs1 > 0 && rs2 > 0)) {
			return false;
		}
		else if ((ls1 > 0 && ls2 > 0) and (rs1 == 0 || rs2 == 0)) {
			return true;
		}
		else return a.first < b.first;
	});



	auto it2 = std::min_element(wire_map_steps.begin(), wire_map_steps.end(), [](std::pair<Coord, std::pair<int, int>> a, std::pair<Coord, std::pair<int, int>> b) {
		int ls1, ls2, rs1, rs2;
		ls1 = a.second.first;
		ls2 = a.second.second;
		rs1 = b.second.first;
		rs2 = b.second.second;

		if ((ls1 == 0 || ls2 == 0) and (rs1 > 0 && rs2 > 0)) {
			return false;
		}
		else if ((ls1 > 0 && ls2 > 0) and (rs1 == 0 || rs2 == 0)) {
			return true;
		}
		else return (a.second.first + a.second.second) < (b.second.first + b.second.second);
	});



	std::cout << "Part 1 solution  : " << it1->first.x + it1->first.y << "\n";
	std::cout << "Part 2 solution  : " << it2->second.first + it2->second.second << "\n";
	std::cout << "\n";


}