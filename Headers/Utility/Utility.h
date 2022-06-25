#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

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

inline double RandomDouble()
{
	static std::uniform_real_distribution dist{ 0.0, 1.0 };
	static std::mt19937 mt{ rd() };

	return dist(mt);
}

inline double RandomDouble(double min, double max)
{
	static std::uniform_real_distribution dist{ min, max };
	static std::mt19937 mt{ rd() };

	return dist(mt);
}

template <typename T>
inline T Clamp(T x, T min, T max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}


// Common Headers

#include <Renderer/Ray.h>
#include <Math/Vector3.h>



#endif