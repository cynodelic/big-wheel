#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <random>
#include "../big_wheel.hpp"

#ifndef CRUSH_LEVEL
#define CRUSH_LEVEL 0
#endif

extern "C"
{
#include "unif01.h"
#include "bbattery.h"
}

using namespace std;

big_wheel_engine<> eng;

uint32_t rand_function()
{
	return eng();
}

int main(int argc,char **argv)
{
	unif01_Gen *gen;
	gen = unif01_CreateExternGenBits("big_wheel",rand_function);

#if CRUSH_LEVEL == 0
	bbattery_SmallCrush(gen);
#endif
#if CRUSH_LEVEL == 1
	bbattery_Crush(gen);
#endif
#if CRUSH_LEVEL == 2
	bbattery_BigCrush(gen);
#endif

	unif01_DeleteExternGenBits(gen);
}

