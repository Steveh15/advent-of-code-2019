#pragma once
#include <iostream>
#include <string>
#include <numeric>

namespace Day16 {

	int get_phase(const int & i, const int & k) {
		int mod = (i + 1) % (4 * k);
		if (mod < k) return 0;
		else if (mod < 2 * k) return 1;
		else if (mod < 3 * k) return 0;
		else return -1;
	}

	void FFT(std::string &  input, int offset) {
		for (int i = 0 + offset; i < input.size(); i++) {
			int sum = 0;
			int j = i;
			for (std::string::iterator it = input.begin() + i; it != input.end(); it++) {
				int c = *it - '0';
				sum += c * get_phase(j, i + 1);
				j++;
			}
			input[i] = '0' + abs(sum % 10);
		}
	}

	void solution() {
		std::string input = "59705379150220188753316412925237003623341873502562165618681895846838956306026981091618902964505317589975353803891340688726319912072762197208600522256226277045196745275925595285843490582257194963750523789260297737947126704668555847149125256177428007606338263660765335434914961324526565730304103857985860308906002394989471031058266433317378346888662323198499387391755140009824186662950694879934582661048464385141787363949242889652092761090657224259182589469166807788651557747631571357207637087168904251987880776566360681108470585488499889044851694035762709053586877815115448849654685763054406911855606283246118699187059424077564037176787976681309870931";

		std::string in1 = input;
		for (int i = 0; i < 100; i++)
			FFT(in1,0);
		std::cout << "Part 1 solution: " << in1.substr(0,8) << "\n";

		// 'Cheat' method which relies on the cut off being in the second half of the input string, which is apparently always is
		std::string p2_input = "";

		for (int i = 0; i < 10000; i++)
			p2_input += input;

		int offset = std::stoi(input.substr(0, 7));

		for (int i = 0; i < 100; i++) {
			long int partial_sum = 0;
			for (std::string::reverse_iterator it = p2_input.rbegin(); it != p2_input.rend() - offset; it++) {
				partial_sum += *it - '0';
				*it = '0' + abs(partial_sum % 10);
			}
		}
		std::cout << "Part 2 solution: " << p2_input.substr(offset, 8) << "\n";
	}
};