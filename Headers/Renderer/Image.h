#ifndef IMAGE_H
#define IMAGE_H

struct Image
{
	const double AspectRatio{ 16.0 / 9.0 };
	const int ImageHeight{ 1080 };
	const int ImageWidth{ static_cast<int>(ImageHeight * AspectRatio) };
	const int SamplesPerPixel{ 100 };
	const int MaxDepth{ 50 };
};

#endif