#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdint>
#include <random>
#include <chrono>
#include "../big_wheel.hpp"

int main()
{
	std::stringstream ss;
	
	std::random_device rd;
	std::uint32_t rdv = rd();
	std::uint32_t ctm = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::uint32_t seed_ = ((rdv^(rdv << 16)) + (ctm^(ctm >> 16)))^0xaaaaaaaa;
	
	ctm = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::uint32_t dsc = (((rdv^(rdv >> 16)) + (ctm^(ctm << 16)) + 1234321)^0xc3c3c3c3) >> 6;
	
	big_wheel rnd1(seed_);
	
	std::cout << "Discarding " << dsc << " times...\n";
	rnd1.discard(dsc);
	
	std::cout << "Storing PRNG's state into a string stream...\n";
	ss << rnd1;
	
	std::cout << "Initializing another PRNG from the previous string stream...\n";
	big_wheel rnd2;
	ss >> rnd2;
	
	std::cout << "Checking if the outputs from both generators are the same...\n";
	
	const std::size_t expected = 10000000;
	std::size_t equals_ = 0;
	for (std::size_t i=0;i<expected;i++)
		if (rnd1() == rnd2())
			equals_++;
	
	std::cout << "Expected: " << expected << ", correct: " << equals_ << "\n";
	
	if (expected == equals_)
		std::cout << " ==> Everything works fine!\n";
}

