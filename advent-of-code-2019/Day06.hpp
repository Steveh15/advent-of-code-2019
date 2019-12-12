#pragma once

#include "get_input.hpp"
#include <regex>
#include <map>
#include <string>

namespace Day6 {

	void solution()
	{

		std::cout << "Day 6 solutions!\n";
		std::vector<std::string> orbit_list = get_lines("day06.txt");

		std::regex planet_regex("(\\w+)\\)(\\w+)");

		std::string str1, str2;
		std::map<std::string, std::vector<std::string>> orbit_map;
		std::map<std::string, std::string> parent_map;

		for (auto o : orbit_list) {
			str1 = std::regex_replace(o, planet_regex, "$1");
			str2 = std::regex_replace(o, planet_regex, "$2");
			orbit_map[str1].push_back(str2);
			orbit_map[str2];
			parent_map[str2] = str1;
		}

		int count = 0;
		std::string planet;
		for (auto p : orbit_map) {
			planet = p.first;
			do {
				planet = parent_map[planet];
				if (planet != "") count += 1;
			} while (planet != "");
		}

		std::cout << "Part one solution : " << count << "\n";

		std::vector<std::string> santa_parents;
		std::vector<std::string> you_parents;
		std::string common_parent = "";

		planet = parent_map["SAN"];
		do {
			santa_parents.push_back(planet);
			planet = parent_map[planet];
		} while (planet != "");

		planet = parent_map["YOU"];
		do {
			you_parents.push_back(planet);
			planet = parent_map[planet];
			auto common = std::find(santa_parents.begin(), santa_parents.end(), planet);
			if (common != santa_parents.end()) {
				common_parent = *common;
			}
		} while (common_parent == "");

		auto santa_common_it = std::find(santa_parents.begin(), santa_parents.end(), common_parent);
		std::cout << "Part two solution : " << (santa_common_it - santa_parents.begin()) + you_parents.size() << "\n";
		std::cout << "\n";
	};

}