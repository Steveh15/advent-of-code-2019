#pragma once

#include <iostream>
#include <vector>

#include "get_input.hpp"


namespace Day1 {

	void p1();
	void solution();


	void p1(){


		std::cout << "Running solution for part 1\n";



		std::vector<std::string> track = get_lines<std::string>("day13.txt");


		for (auto s : track) {
			std::cout << s << "\n";
		}
	};



	void solution() {




		p1();



	};


}