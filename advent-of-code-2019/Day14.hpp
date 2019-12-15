#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <regex>
#include "get_input.hpp"

namespace Day14 {

	// Taken from https://stackoverflow.com/questions/7007802/erase-specific-elements-in-stdmap
	template <typename Map, typename F>
	void map_erase_if(Map& m, F pred)
	{
		typename Map::iterator i = m.begin();
		while ((i = std::find_if(i, m.end(), pred)) != m.end())
			m.erase(i++);
	}

	struct recipe {
		std::map<std::string, int> ingredients;
		//std::pair<std::string, int> product;
		std::string product;
		int amount;
	};

	void solution() {

		std::cout << "Day 14 solutions!\n";

		std::vector<std::string> input = get_lines("day14.txt");

		std::regex planet_regex("(.*)=>(.*)");
		std::regex ingredient_regex("(\\d+)\\s(\\w+)");
		std::smatch match;

		std::string str1, str2;

		std::vector<recipe> recipe_list;

		for (auto s : input) {
			recipe new_recipe;
			str1 = std::regex_replace(s, planet_regex, "$1");
			str2 = std::regex_replace(s, planet_regex, "$2");

			while (std::regex_search(str1, match, ingredient_regex)) {
				new_recipe.ingredients[match[2]] = stoi(match[1]);
				str1 = match.suffix().str();
			}
			std::regex_search(str2, match, ingredient_regex);
			new_recipe.amount = stoi(match[1]); 
			new_recipe.product = match[2];
			recipe_list.push_back(new_recipe);
		}

		std::cout << "Part 1 solution: " << "\n";
		std::cout << "\n";

		for (auto r : recipe_list) {
			for (auto i : r.ingredients) {
				std::cout << i.first << " " << i.second << ", ";
			}
			std::cout << " => " << r.product << " " << r.amount << "\n";
		}

		std::cout << "\n\n";

		std::map<std::string, int> need_pile;
		std::map<std::string, int> excess_pile;
		need_pile["FUEL"] = 1;

		while (std::find_if(need_pile.begin(), need_pile.end(), [](auto& a) {
			return  a.first != "ORE" && a.second != 0;
		}) != need_pile.end()) {

		// Select first item which isn't 0;
		std::string need_item = std::find_if(need_pile.begin(), need_pile.end(), [](auto &a) {
			return  a.first != "ORE" && a.second != 0;
		})->first;

		// Compare to excess pile
		int have_n = excess_pile[need_item];
		int need_n = need_pile[need_item];
		if (have_n >= need_n) {
			need_pile[need_item] -= need_n;
			excess_pile[need_item] -= need_n;
		}
		else {
			// if have = 0 then nothing will happen
			need_pile[need_item] -= have_n;
			excess_pile[need_item] -= have_n;
		}

		// Buy item
		// Find relevant recipe
		auto need_recipe = std::find_if(recipe_list.begin(), recipe_list.end(), [need_item](auto & a) {
			return need_item == a.product;
		});
		// Work out how many times you need to make recipe
		int buy_n = 1;
		while (buy_n * need_recipe->amount < need_n) {
			buy_n += 1;
		}

		// Check if excess is made
		if (need_recipe->amount * buy_n > need_n) {
			excess_pile[need_item] += (buy_n * need_recipe->amount) - need_n;
		}

		// Remove item from need pile, add ingredients to need pile
		need_pile[need_item] = 0;

		for (auto i : need_recipe->ingredients) {
			need_pile[i.first] += buy_n * i.second;
		}

		// Clean maps (useful for debugging)
		map_erase_if(need_pile, [](auto a) { return a.second == 0; });
		map_erase_if(excess_pile, [](auto a) { return a.second == 0; });


		// Print current need plie;
		std::cout << "Current need item = " << need_item << "\n";
		std::cout << "Need # ";
		for (auto n : need_pile) std::cout << n.first << ": " << n.second << ", ";
		std::cout << "\nExcess # ";
		for (auto n : excess_pile) std::cout << n.first << ": " << n.second << ", ";

		std::cout << "\n\n";

		}





		//for (auto i : need_recipe->ingredients) {
		//	std::cout << i.first << " " << i.second << ", ";
		//}
		//std::cout << " => " << need_recipe->product << " " << need_recipe->amount << "\n";


		//std::cout << need_item << " - " << need_pile[need_item] << "\n";


	}



	// Two piles, a need pile and an excess pile (need pile starts with "1 FUEL", excress pile starts empty
	// Performing following loop
	//   1) Pick an item in the need pile
	//   2) Check if item is in the excess pile. If it is remove correct amount from both piles
	//     3.1) Find recipe which creates the needed item
	//     3.2) Find how many times you need to make recipe. If you end up with more of the needed item that required, then add excess to excess pile
	//     3.3) Remove needed item from need pile. Add recipe ingredients to need pile;
	//   4) If picked item is "ORE" then skip 2 and 3 and just remove from need pile whilst adding amount to ore spent pile
	// Repeat loop until nothing left in need pile

	// Order which reactions completed is important, need to perform higher order recipes first
	// 0th order product = FUEL
	// 1st order product = stuff needed to make fuel
	// 2nd order product = stuff needed to make the stuff needed to make fuel
	// i.e. perform reactions in order they are added to need pile


};