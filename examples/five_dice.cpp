#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <random>
#include <chrono>
#include "../big_wheel.hpp"

int main(int argc,char **argv)
{
	std::random_device rd;
	std::seed_seq ssq = {
		rd(),
		std::uint32_t(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
		rd(),
		std::uint32_t(std::chrono::high_resolution_clock::now().time_since_epoch().count())
	};
	big_wheel rnd(ssq);
	std::uniform_int_distribution<int> dst(1,6);
	
	std::cout << "Result of 5 thrown dice:";
	for (std::size_t i=0;i<5;i++)
		std::cout << " " << dst(rnd);
	std::cout << "\n";
}

