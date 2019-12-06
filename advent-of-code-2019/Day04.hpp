#pragma once

#include <cmath>


namespace Day4 {

	int nthDigit(const int & i, const int & n) {
		return (i % (int)pow(10, n))/(int)pow(10,n-1);
	}

	bool checkPassword(int pass) {
		bool test1 = 
			(nthDigit(pass, 6) <= nthDigit(pass, 5)) && 
			(nthDigit(pass, 5) <= nthDigit(pass, 4)) && 
			(nthDigit(pass, 4) <= nthDigit(pass, 3)) && 
			(nthDigit(pass, 3) <= nthDigit(pass, 2)) && 
			(nthDigit(pass, 2) <= nthDigit(pass, 1));
		bool test2 = 
			(nthDigit(pass, 6) == nthDigit(pass, 5)) || 
			(nthDigit(pass, 5) == nthDigit(pass, 4)) || 
			(nthDigit(pass, 4) == nthDigit(pass, 3)) || 
			(nthDigit(pass, 3) == nthDigit(pass, 2)) || 
			(nthDigit(pass, 2) == nthDigit(pass, 1));
		return test1 && test2;
	}

	bool checkPasswordPart2(int pass) {
		bool test1 = 
			(nthDigit(pass, 6) <= nthDigit(pass, 5)) && 
			(nthDigit(pass, 5) <= nthDigit(pass, 4)) && 
			(nthDigit(pass, 4) <= nthDigit(pass, 3)) && 
			(nthDigit(pass, 3) <= nthDigit(pass, 2)) && 
			(nthDigit(pass, 2) <= nthDigit(pass, 1));
		bool test2 = 
			(nthDigit(pass, 6) == nthDigit(pass, 5) && nthDigit(pass, 5) != nthDigit(pass, 4)) ||
			(nthDigit(pass, 5) == nthDigit(pass, 4) && nthDigit(pass, 6) != nthDigit(pass, 5) && nthDigit(pass, 4) != nthDigit(pass, 3)) ||
			(nthDigit(pass, 4) == nthDigit(pass, 3) && nthDigit(pass, 5) != nthDigit(pass, 4) && nthDigit(pass, 3) != nthDigit(pass, 2)) ||
			(nthDigit(pass, 3) == nthDigit(pass, 2) && nthDigit(pass, 4) != nthDigit(pass, 3) && nthDigit(pass, 2) != nthDigit(pass, 1)) ||
			(nthDigit(pass, 2) == nthDigit(pass, 1) && nthDigit(pass, 3) != nthDigit(pass, 2));
		return test1 && test2;
	}


	void solution() {
		std::cout << "Day 4 solutions!\n";

		std::vector<int> valid_passwords;
		std::vector<int> valid_passwords_2;

		for (int k = 246515; k <= 739105; k++) {
			if (checkPassword(k)) valid_passwords.push_back(k);
			if (checkPasswordPart2(k)) valid_passwords_2.push_back(k);
		}

		std::cout << "Part 1 solution  : " << valid_passwords.size() << "\n";
		std::cout << "Part 2 solution  : " << valid_passwords_2.size() << "\n";
		std::cout << "\n";
	}

};