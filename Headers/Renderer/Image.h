#ifndef IMAGE_H
#define IMAGE_H

#include <Parallel.h>

struct Image
{
	double AspectRatio{ 16.0 / 9.0 };
	int ImageHeight{ 1080 };
	int ImageWidth{ static_cast<int>(ImageHeight * AspectRatio) };
	int SamplesPerPixel{ 100 };
	int MaxDepth{ 50 };

	void SetSamplesAsMultipleOfTheads()
	{
		int remainder = SamplesPerPixel % g_THREAD_COUNT;

		if (remainder == 0) return;

		SamplesPerPixel += (g_THREAD_COUNT - remainder);
	}

};

#endif