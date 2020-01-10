#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>


namespace Day16 {

	int nthDigit(const int& i, const int& n) {
		return (i % (int)pow(10, n)) / (int)pow(10, n - 1);
	}

	int get_phase(const int & i, const int & k) {
		int mod = (i + 1) % (4 * k);
		if (mod < k) return 0;
		else if (mod < 2 * k) return 1;
		else if (mod < 3 * k) return 0;
		else if (mod < 4 * k) return -1;
		return -2;
	}

	std::string FFT(std::string input) {
		std::string output = "";


		for (int i = 0; i < input.size(); i++) {
			int phase = i + 1;
			int sum = 0;
			int j = i;
			//for (auto c2 : input) {
			for(std::string::iterator it = input.begin() + i; it != input.end(); it++ ){
				int c = (int)*it - 48;
				sum += c * get_phase(j, phase);
				j++;
			}
			output += std::to_string(abs(nthDigit(sum, 1)));
		}

		return output;
	}

	std::string FFT2(std::string input, int offset) {
		std::string output = "";


		for (int i = 0; i < input.size(); i++) {
			int phase = i + 1 + offset;
			int sum = 0;
			int j = i + offset;
			for (std::string::iterator it = input.begin() + i; it != input.end(); it++) {
				int c = (int)*it - 48;
				sum += c * get_phase(j, phase);
				//std::cout << c << "*" << get_phase(j, phase) << " + ";
				j++;
			}
			//std::cout << "  Sum " << i << " : " <<  sum << "\n";
			output += std::to_string(abs(nthDigit(sum, 1)));
		}

		return output;
	}
	using number_t = std::vector<int>;

	number_t from_string(std::string const& text)
	{
		number_t number;

		for (auto const& ch : text)
			number.push_back(ch - '0');

		return number;
	}

	std::string to_string(number_t const& number)
	{
		std::stringstream sstr;
		for (auto const& e : number)
			sstr << static_cast<char>(e + '0');
		return sstr.str();
	}

	std::string get_message(std::string input, long long const phases, size_t const length)
	{
		auto bnumber = from_string(input);
		auto offset = std::stoi(input.substr(0, 7));
		std::cout << "Offset : " << offset << "\n";
		//auto offset = 1;
		auto number = number_t{};
		for (int i = 0; i < 10000; ++i)
			number.insert(number.end(), bnumber.begin(), bnumber.end());

		for (long long i = 0; i < phases; ++i)
		{
			auto partial_sum = std::accumulate(
				std::begin(number) + offset,
				std::end(number),
				0ll,
				[](long long const sum, int const v) {return sum + v; });

			for (size_t j = offset; j < number.size(); ++j)
			{
				auto t = partial_sum;
				partial_sum -= number[j];
				number[j] = t >= 0 ? t % 10 : (-t) % 10;
			}
		}

		number_t result(number.begin() + offset, number.begin() + offset + length);

		return to_string(result);
	}


	void solution() {


		//std::string input = "59705379150220188753316412925237003623341873502562165618681895846838956306026981091618902964505317589975353803891340688726319912072762197208600522256226277045196745275925595285843490582257194963750523789260297737947126704668555847149125256177428007606338263660765335434914961324526565730304103857985860308906002394989471031058266433317378346888662323198499387391755140009824186662950694879934582661048464385141787363949242889652092761090657224259182589469166807788651557747631571357207637087168904251987880776566360681108470585488499889044851694035762709053586877815115448849654685763054406911855606283246118699187059424077564037176787976681309870931";
		std::string input = "03081770884921959731165446850517";
		//input = "12345678";

		std::string in1 = input;
		for (int i = 0; i < 100; i++) {
			in1 = FFT(in1);

		}
		//in1.resize(8);
		std::cout << in1 << "\n";



		//std::string in2 = "345678";
		//for (int i = 0; i < 100; i++) {
		//	in2 = FFT2(in2,2);
		//}
		//std::cout << in2 << "\n";

		//for (int i = 0; i < 100; i++) {
		//	std::cout << "FFT " << i << "\n";
		//	in2 = FFT(in2);
		//}




		//std::string in2 = "";
		//in2 = "";
		//std::string offset = input;
		//offset.resize(7);
		//int offset_n = stoi(offset);
		//for (int i = 0; i < 10000; i++) {
		//	in2 += input;
		//}

		//std::cout << in2 << "\n";
		//std::cout << "Offset : " << offset_n << "\n";

		//std::cout << "original size : " << in2.size() << "\n";
		//std::string reduced_string = in2.substr(offset_n);
		//std::cout << "new size : " << reduced_string.size() << "\n";

		//for (int i = 0; i < 100; i++) {
		//	std::cout << "FFT " << i << "\n";
		//	in2 = FFT2(reduced_string, offset_n);
		//}


		//std::cout << "\n\n";
		//std::cout << in2 << "\n";

		input = "03081770884921959731165446850517";
		auto message = get_message(input, 100, 8);
		std::cout << "Part 2 " << message << "\n";

		//input = "12345678";
		//message = get_message(input, 4, 8);
		//std::cout << "Part 2 " << message << "\n";

		// OPtimisation
		// 1 Don't calculate the beginning zeros
		// 2 Only calculate starting at the offset


	}
};