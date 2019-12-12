#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <queue>
#include <array>
namespace Day12 {


	struct moon {
		int x, y, z, vx, vy, vz;
	};

	std::ostream& operator<<(std::ostream& out, const moon& moon) {
		out << "(" << moon.x << ", " << moon.y << ", " << moon.z << ") " << "  v(" << moon.vx << ", " << moon.vy << ", " << moon.vz << ") ";
		return out;
	}

	void updateVelocity(moon& m1, moon& m2) {
		if (m1.x > m2.x) { m1.vx -= 1; m2.vx += 1; }
		else if (m1.x < m2.x) { m1.vx += 1; m2.vx -= 1; }

		if (m1.y > m2.y) { m1.vy -= 1; m2.vy += 1; }
		else if (m1.y < m2.y) { m1.vy += 1; m2.vy -= 1; }

		if (m1.z > m2.z) { m1.vz -= 1; m2.vz += 1; }
		else if (m1.z < m2.z) { m1.vz += 1; m2.vz -= 1; }
	}

	void updateVelocitys(std::vector<moon>& moons) {
		for (int i = 0; i < moons.size(); i++) {
			for (int j = i; j < moons.size(); j++) {
				//std::cout << "??\n";
				updateVelocity((moons[i]), (moons[j]));
			}
		}
	}

	void updatePositions(std::vector<moon>& moons) {
		for (auto& moon : moons) {
			moon.x += moon.vx;
			moon.y += moon.vy;
			moon.z += moon.vz;
		}
	}

	std::array<int, 4> getAxis(std::vector<moon> moons, char c) {
		std::array<int, 4> axis;
		if (c == 'x') axis = { moons[0].x, moons[1].x, moons[2].x, moons[3].x };
		else if (c == 'y') axis = { moons[0].y, moons[1].y, moons[2].y, moons[3].y };
		else if (c == 'z') axis = { moons[0].z, moons[1].z, moons[2].z, moons[3].z };
		return axis;
	}



	void solution() {

		std::cout << "Day 12 solutions!\n";

		std::vector<moon> moons;
		moons.push_back({ 14,  9, 14, 0,0,0 });
		moons.push_back({  9, 11,  6, 0,0,0 });
		moons.push_back({ -6, 14, -4, 0,0,0 });
		moons.push_back({  4, -4, -3, 0,0,0 });

		for (int i = 0; i < 1000; i++) {
			updateVelocitys(moons);
			updatePositions(moons);
		}

		double energy = std::accumulate(moons.begin(), moons.end(), 0, [](double a, moon b) {
			return a + (abs(b.x) + abs(b.y) + abs(b.z)) * (abs(b.vx) + abs(b.vy) + abs(b.vz));
		});






		std::cout << "Part 1 solution: " << energy << "\n";
		std::cout << "\n";

		// Each axis is independent
		// Find how long it takes for each axis to repeat 
		// Lowest common multiple is the time it takes for whole system to repeat

		//std::array<int, 4> x_axis_now = { 14,9,-6,4 };

		//int x_repeat = 0, y_repeat = 0, z_repeat = 0;
		////reset moons
		//moons.clear()
		//moons.push_back({ 14,  9, 14, 0,0,0 });
		//moons.push_back({ 9, 11,  6, 0,0,0 });
		//moons.push_back({ -6, 14, -4, 0,0,0 });
		//moons.push_back({ 4, -4, -3, 0,0,0 });
		//std::array<int, 4> x_axis_initial = { 14, 9,  -6,  4 };
		//std::array<int, 4> y_axis_initial = { 9, 11, 14, -4 };
		//std::array<int, 4> z_axis_initial = { 14,  6, -4, -3 };

		//while (x_repeat == 0 or y_repeat == 0 or x_repeat == 0) {

		//}

		//if (x_axis_initial == x_axis_now) {
		//	std::cout << "This works!";
		//}




		//std::cout << moons[0] << "\n";
		//std::cout << moons[1] << "\n";
		//std::cout << moons[2] << "\n";
		//std::cout << moons[3] << "\n";
		//std::array<int, 4> test_axis = getAxis(moons, 'x');
		//std::cout << test_axis[0] << ", " << test_axis[1] << ", " << test_axis[2] << ", " << test_axis[3] << "\n";


	}
};