#pragma once


#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>




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
	std::string wire1 = input_lines[0];
	std::string wire2 = input_lines[1];

	std::istringstream stream1;

	char c, comma;
	int m;

	std::unordered_map<Coord, int> wire_map;
	int current_x = 0;
	int current_y = 0;

	stream1.str(wire1);

	while (stream1.good()) {
		stream1 >> c >> m >> comma;
		for (int i = 1; i <= m; i++) {
			if (c == 'R') {
				current_x += 1;
			}
			else if (c == 'L') {
				current_x -= 1;
			}
			else if (c == 'U') {
				current_y += 1;
			}
			else if (c == 'D') {
				current_y -= 1;
			}
			wire_map[{current_x, current_y }] = 1;
		}
	}

	current_x = 0;
	current_y = 0;

	stream1.clear();
	stream1.str(wire2);

	while (stream1.good()) {
		stream1 >> c >> m >> comma;

		for (int i = 1; i <= m; i++) {

			if (c == 'R') {
				current_x += 1;
			}
			else if (c == 'L') {
				current_x -= 1;
			}
			else if (c == 'U') {
				current_y += 1;
			}
			else if (c == 'D') {
				current_y -= 1;
			}
			wire_map[{current_x, current_y }] += 1;
		}
	}




	auto it = std::min_element(wire_map.begin(), wire_map.end(), [](std::pair<Coord, int> a, std::pair<Coord, int> b) {

		if (a.second == 1 and b.second > 1) {
			return false;
		} 
		else if (a.second > 1 and b.second == 1) {
			return true;
		}
		else return a.first < b.first;

	});

	std::cout << "Part 1 solution  : " << it->first.x + it->first.y << "\n";




	std::unordered_map<Coord, std::pair<int,int>> wire_map_steps;
	current_x = 0;
	current_y = 0;
	int steps = 0;

	stream1.clear();
	stream1.str(wire1);

	while (stream1.good()) {
		stream1 >> c >> m >> comma;
		for (int i = 1; i <= m; i++) {
			steps += 1;
			if (c == 'R') {
				current_x += 1;
			}
			else if (c == 'L') {
				current_x -= 1;
			}
			else if (c == 'U') {
				current_y += 1;
			}
			else if (c == 'D') {
				current_y -= 1;
			}
			if (wire_map_steps[{current_x, current_y }].first == 0) 
				wire_map_steps[{current_x, current_y }].first = steps;

		}
	}

	current_x = 0;
	current_y = 0;

	stream1.clear();
	stream1.str(wire2);

	steps = 0;

	while (stream1.good()) {
		stream1 >> c >> m >> comma;

		for (int i = 1; i <= m; i++) {
			steps += 1;
			if (c == 'R') {
				current_x += 1;
			}
			else if (c == 'L') {
				current_x -= 1;
			}
			else if (c == 'U') {
				current_y += 1;
			}
			else if (c == 'D') {
				current_y -= 1;
			}
			if (wire_map_steps[{current_x, current_y }].second == 0)
				wire_map_steps[{current_x, current_y }].second = steps;
		}
	}

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

	std::cout << "Part 2 solution  : " << it2->second.first + it2->second.second;



}