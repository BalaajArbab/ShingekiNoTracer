#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <Parallel.h>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


// Constants

inline const double infinity = std::numeric_limits<double>::infinity();
inline const double pi = 3.1415926535897932385;

inline std::random_device rd;


// Utility Functions

inline double DegreesToRadians(double degrees)
{
	return (pi * degrees) / 180.0;
}

inline double RandomDouble(int id = 0)
{
	thread_local std::uniform_real_distribution dist{ 0.0, 1.0 };

	return dist(g_RNGS[id]);
}

inline double RandomDouble(double min, double max, int id = 0)
{
	std::uniform_real_distribution dist{ min, max };

	return dist(g_RNGS[id]);
}

inline std::int32_t RandomInteger(std::int32_t min, std::int32_t max, int id = 0)
{
	std::uniform_int_distribution dist{ min, max };

	return dist(g_RNGS[id]);
}

template <typename T>
inline T Clamp(T x, T min, T max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}


#endif