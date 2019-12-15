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
		std::map<std::string, __int64> ingredients;
		//std::pair<std::string, __int64> product;
		std::string product;
		__int64 amount;
	};



	__int64 calculateOre(__int64 fuel, std::vector<recipe> recipe_list) {




		std::vector<std::pair<std::string, __int64>> need_pile;
		std::map<std::string, __int64> excess_pile;
		need_pile.push_back(std::make_pair("FUEL", fuel));

		while (std::find_if(need_pile.begin(), need_pile.end(), [](auto& a) {
			return  a.first != "ORE";
		}) != need_pile.end()) {

			// Select first item which isn't 0;
			auto need_it = std::find_if(need_pile.begin(), need_pile.end(), [](auto& a) {
				return  a.first != "ORE" && a.second != 0;
			});

			std::string need_item = need_it->first;

			__int64 have_n = excess_pile[need_item];
			__int64 need_n = need_it->second;

			if (have_n >= need_n) {
				// If have more than need adjust amounts then stop;
				need_it->second -= need_n;
				excess_pile[need_item] -= need_n;
				need_n = 0;
			}
			else {
				// if have = 0 then nothing will happen
				need_n -= have_n;
				excess_pile[need_item] -= have_n;

				// Buy item
				// Find relevant recipe
				auto need_recipe = std::find_if(recipe_list.begin(), recipe_list.end(), [need_item](auto& a) {
					return need_item == a.product;
				});
				// Work out how many times you need to make recipe
				__int64 buy_n = 0;
				while (buy_n * need_recipe->amount < need_n) {
					buy_n += 1;
				}

				// Check if excess is made
				if (need_recipe->amount * buy_n > need_n) {
					excess_pile[need_item] += (buy_n * need_recipe->amount) - need_n;
				}

				// Remove item from need pile, add ingredients to need pile
				need_it->second = 0;

				for (auto i : need_recipe->ingredients) {
					// Find ingredient in need pile
					auto it = std::find_if(need_pile.begin(), need_pile.end(), [i](auto& a) {
						return a.first == i.first;
					});
					if (it == need_pile.end()) {
						need_pile.push_back(std::make_pair(i.first, buy_n * i.second));
					}
					else it->second += buy_n * i.second;
				}
			}

			// Clean maps (useful for debugging)
			//map_erase_if(need_pile, [](auto a) { return a.second == 0; });
			need_pile.erase(std::remove_if(need_pile.begin(), need_pile.end(), [](auto& a) { return a.second == 0;  }), need_pile.end());
			map_erase_if(excess_pile, [](auto a) { return a.second == 0; });


			// print current need plie;
			/*std::cout << "Current need item = " << need_item << "\n";
			std::cout << "Need # ";*/
			//for (auto n : need_pile) std::cout << n.first << ": " << n.second << ", ";
			////std::cout << "\nExcess # ";
			//for (auto n : excess_pile) std::cout << n.first << ": " << n.second << ", ";

			//std::cout << "\n\n";

		}


		//__int64 ore_per_fuel = need_pile.front().second;
		//std::cout << "Part 1 solution: " << ore_per_fuel << "\n";
		//std::cout << "\n";

		return need_pile.front().second;

	}



	void solution() {

		std::cout << "Day 14 solutions!\n";

		std::vector<std::string> input = get_lines("day14.txt");
		std::vector<recipe> recipe_list;

		for (auto s : input) {
			recipe new_recipe;

			std::regex recipe_regex("(.*)=>(.*)");
			std::regex ingredient_regex("(\\d+)\\s(\\w+)");
			std::string  str1 = std::regex_replace(s, recipe_regex, "$1");
			std::string  str2 = std::regex_replace(s, recipe_regex, "$2");

			std::smatch match;

			while (std::regex_search(str1, match, ingredient_regex)) {
				new_recipe.ingredients[match[2]] = stoi(match[1]);
				str1 = match.suffix().str();
			}
			std::regex_search(str2, match, ingredient_regex);
			new_recipe.amount = stoi(match[1]);
			new_recipe.product = match[2];
			recipe_list.push_back(new_recipe);
		}


		__int64 ore_per_fuel = calculateOre(1, recipe_list);
		std::cout << "Part 1 solution: " << ore_per_fuel << "\n";




		// Lower limit


		__int64 lower_limit = 1000000000000 / ore_per_fuel;
		__int64 upper_limit = lower_limit * 2;

		bool found_solution = false;
		__int64 guess;

		while (!found_solution) {

			guess = (lower_limit + upper_limit) / 2;
			std::cout << "Guess: " << guess << "\n";
			__int64 fn = calculateOre(guess, recipe_list);
			__int64 fnp1 = calculateOre(guess + 1, recipe_list);

			if (fn > 1000000000000) upper_limit = guess;
			else if (fnp1 > 1000000000000) found_solution = true;
			else lower_limit = guess;
		}


		std::cout << "Part 2 solution: " << guess << "\n";

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
	// Perform reactions in order they are added to the need pile


};