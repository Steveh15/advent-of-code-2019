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

	//bool operator<(const Coord& lhs, const Coord& rhs) {
	//	if (lhs.x != rhs.x) 
	//		return lhs.x < rhs.x;
	//	else return lhs.y < rhs.y;
	//}


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


	//wire1 = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
	//wire2 = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

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




	//for (auto& p : wire_map) {
	//	std::cout << "MAP : " << p.first.x << ", " << p.first.y << " - " << p.second << "\n";
	//}




	auto it = std::min_element(wire_map.begin(), wire_map.end(), [](std::pair<Coord, int> a, std::pair<Coord, int> b) {
		
		//return a.second > b.second;
		if (a.second == 1 and b.second > 1) {
			return false;
		}
		else if (a.second > 1 and b.second == 1) {
			return true;
		} else return a.first < b.first;


	/*	if (a.second > 1 && b.second == 1)
			return true;
		*/

		//return  a.first < b.first;
	});

	//std::cout << "Min! : " << it->first.x << ", " << it->first.y;
	std::cout << "Part 1 solution  : " << it->first.x + it->first.y;
}