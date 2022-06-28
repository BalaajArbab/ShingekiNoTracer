#ifndef IMAGE_H
#define IMAGE_H

struct Image
{
	double AspectRatio{ 16.0 / 9.0 };
	int ImageHeight{ 1080 };
	int ImageWidth{ static_cast<int>(ImageHeight * AspectRatio) };
	int SamplesPerPixel{ 100 };
	int MaxDepth{ 50 };
};

#endif