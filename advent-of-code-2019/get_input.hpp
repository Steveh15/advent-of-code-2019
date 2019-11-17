#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>




// Util for importing text file line by line as strings
//template<typename T>
std::vector<std::string> get_lines(std::string file) {

	std::ifstream is("../inputs/" + file);

	if (!is.is_open()) {
		throw std::runtime_error("Could not open puzzle input file");
	}

	std::vector<std::string> v;
	std::string t;
	std::string line;
	while (getline(is, line)) {
		v.push_back(line);
	}
	return v;

};



// Util for importing text file as custom type
template<typename T>
std::vector<T> get_input(std::string file) {

	std::ifstream is("../inputs/" + file);

	if (!is.is_open()) {
		throw std::runtime_error("Could not open puzzle input file");
	}

	std::vector<T> v;
	T t;
	while (is >> t) {
		v.push_back(t);
	}
	return v;

};
