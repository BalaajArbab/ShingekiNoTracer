#ifndef PARALLEL_H
#define PARALLEL_H

#include <random>
#include <mutex>

inline const int g_THREAD_COUNT = 2; // Keep this an even divisor of samplesPerPixel
inline std::mutex mtx;

inline std::mt19937 g_RNGS[g_THREAD_COUNT];

inline std::random_device g_RD;

inline void InitializeRNGS()
{
	for (int i = 0; i < g_THREAD_COUNT; ++i)
	{
		g_RNGS[i] = std::mt19937{ g_RD() };
	}

}



#endif