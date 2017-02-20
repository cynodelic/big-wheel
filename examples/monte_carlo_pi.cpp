#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdint>
#include <thread>
#include <future>
#include <random>
#include <vector>
#include <chrono>
#include "../big_wheel.hpp"

typedef struct
{
	double x, y, z;
} point_t;

static const double PI = 3.1415926535897932384626433832795;
static const std::uint32_t prng_max_value = big_wheel_engine<>::max();

double approximate_pi(std::uint32_t pc,std::uint32_t tp)
{
	return 4.0*(double(pc)/double(tp));
}

double pi_error(double x)
{
	return 100.0*((x-PI)/PI);
}

std::uint32_t generate_points(std::uint32_t nppt)
{
	std::random_device rd;
	std::uint32_t seed[16] = {0x0};
	
	for (int i=0;i<16;i++)
		seed[i] = rd();
	
	big_wheel_engine<> rgen(
		seed[ 0],seed[ 1],seed[ 2],seed[ 3],
		seed[ 4],seed[ 5],seed[ 6],seed[ 7],
		seed[ 8],seed[ 9],seed[10],seed[11],
		seed[12],seed[13],seed[14],seed[15]
	);
		
	std::uint32_t pcnt = 0;
	point_t rpt;
	for (std::uint32_t i=0;i<nppt;i++)
	{
		rpt.x = double(rgen())/static_cast<double>(prng_max_value);
		rpt.y = double(rgen())/static_cast<double>(prng_max_value);
		rpt.z = (rpt.x*rpt.x)+(rpt.y*rpt.y);
		if (rpt.z <= 1.0) pcnt++;
	}
	
	return pcnt;
}

int main(int argc,char **argv)
{
	// Check number of cores
	std::size_t num_cores = std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 1;
	
	// Thread set
	std::vector<std::future<std::uint32_t>> future_set;
	
	const std::uint32_t num_points = 3221225472;
	const std::uint32_t num_points_per_thread = num_points/num_cores;
	
	for (std::size_t i=0;i<num_cores;i++)
		future_set.push_back(
			std::async(
				std::launch::async,
				generate_points,
				num_points_per_thread
			)
		);
	
	// Print info
	std::cout << "Number of points: " << num_points << "\n";
	std::cout << "Number of cores: " << num_cores << "\n";
	std::cout << " ==> Number of points per thread: " << num_points_per_thread << "\n\n";
	
	std::cout << "Generating random points...\n";
	
	std::chrono::high_resolution_clock::time_point tpa = std::chrono::high_resolution_clock::now();
	
	// Number of points inside circle
	std::uint32_t pcnt = 0;
	
	// Sum points inside circle from all threads
	for (auto &ftr : future_set)
		pcnt += ftr.get();
	
	std::chrono::high_resolution_clock::time_point tpb = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> tm = std::chrono::duration_cast<std::chrono::duration<double>>(tpb-tpa);
	
	// Duration
	double dur = tm.count();
	
	// Approximate pi and calculate error
	const double gen_pi = approximate_pi(pcnt,num_points);
	const double pi_err = pi_error(gen_pi);
	
	std::cout << "\nResults:\n";
	std::cout << "  Number of points within circle: " << pcnt << "\n";
	std::cout << "  Pi approximation:               " << std::setprecision(32) << gen_pi << "\n";
	std::cout << "  Error:                          " << std::setprecision(10) << pi_err << "%\n";
	
	std::cout << "Time elapsed: " << std::setprecision(10) << dur << " seconds\n";
}

