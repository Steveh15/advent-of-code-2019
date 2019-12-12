#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <numeric>
namespace Day12 {

	struct moon {
		int x, y, z, vx, vy, vz;
	};

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
		if (c == 'x') return { moons[0].x, moons[1].x, moons[2].x, moons[3].x };
		else if (c == 'y') return { moons[0].y, moons[1].y, moons[2].y, moons[3].y };
		else if (c == 'z') return { moons[0].z, moons[1].z, moons[2].z, moons[3].z };
	}

	void solution() {

		std::cout << "Day 12 solutions!\n";
		std::vector<moon> moons, moons_initial;
		moons.push_back({ 14,  9, 14, 0,0,0 });
		moons.push_back({  9, 11,  6, 0,0,0 });
		moons.push_back({ -6, 14, -4, 0,0,0 });
		moons.push_back({  4, -4, -3, 0,0,0 });
		moons_initial = moons;

		for (int i = 0; i < 1000; i++) {
			updateVelocitys(moons);
			updatePositions(moons);
		}

		double energy = std::accumulate(moons.begin(), moons.end(), 0, [](double a, moon b) {
			return a + (abs(b.x) + abs(b.y) + abs(b.z)) * (abs(b.vx) + abs(b.vy) + abs(b.vz));
		});

		std::cout << "Part 1 solution: " << energy << "\n";
		// Each axis is independent
		// Find how long it takes for each axis to repeat 
		// Lowest common multiple is the time it takes for whole system to repeat

		moons = moons_initial;
		long long int x_repeat = 0, y_repeat = 0, z_repeat = 0, step = 0;

		std::array<int, 4> x_axis_initial = { moons[0].x, moons[1].x,moons[2].x,moons[3].x };
		std::array<int, 4> y_axis_initial = { moons[0].y, moons[1].y,moons[2].y,moons[3].y };
		std::array<int, 4> z_axis_initial = { moons[0].z, moons[1].z,moons[2].z,moons[3].z };

		while (x_repeat == 0 or y_repeat == 0 or z_repeat == 0) {
			step += 1;
			updateVelocitys(moons);		
			updatePositions(moons);
			if (x_repeat == 0 && x_axis_initial == getAxis(moons, 'x')) x_repeat = step;
			if (y_repeat == 0 && y_axis_initial == getAxis(moons, 'y')) y_repeat = step;
			if (z_repeat == 0 && z_axis_initial == getAxis(moons, 'z')) z_repeat = step;
		}
		long long int lcm = std::lcm(x_repeat+1, std::lcm(y_repeat+1, z_repeat+1));
		std::cout << "Part 2 solution: " << lcm << "\n";
		std::cout << "\n";
	}
};