
// Add ./Headers as an include directory.
#include "Headers/ShingekiNoTracer.h"

// Forward Declarations.
Colour rayColour(const Ray& r, const Colour& background, const Hittable& worldObjects, int depth);
void Render(const std::string& filename, const Image& image, const Camera& camera, PixelBuffer& pixelBuffer, const Hittable& worldObjects, const Colour& background);

int g_Count{ 0 };

int main()
{
	// Image
	constexpr double aspectRatio = 16.0 / 9.0;
	constexpr int imageHeight = 600;
	constexpr int imageWidth = static_cast<int>(imageHeight * aspectRatio);
	constexpr int samplesPerPixel = 100;
	constexpr int maxDepth = 50;

	Image image{ aspectRatio, imageHeight, imageWidth, samplesPerPixel, maxDepth };


	// World / Camera
	HittableList worldObjects;
	Colour background{ 0.6, 0.3, 0.1 };
	

	Point3 lookFrom{ 0, 0, 1 };
	Point3 lookAt{ 0, 0, 0 };
	double vFOV = 90.0;

	int scene = 1;

	switch (scene)
	{
	case 0: 
		RandomScene(worldObjects);

		lookFrom = Point3{ 13, 3, 10 };
		lookAt = Point3{ 0, 0, -2 };
		vFOV = 20.0;

		break;
	case 1:
		Scene1(worldObjects);
		break;
	}

	BVHNode bvhTree{ worldObjects };


	// Camera
	Vector3 vUp{ 0, 1, 0 };

	double aperture = 0.01;
	double distToFocusPlane = 100.0;

	//double distToFocusPlane = (lookFrom - lookAt).Magnitude();

	//Camera camera{ lookFrom, lookAt, vUp, vFOV, image.AspectRatio, aperture, distToFocusPlane, 0 };


	// Render
	int frameCount = 1;
	double angleIncrement = 360 / frameCount;

	Stopwatch sw;
	sw.Start();

	PixelBuffer pixelBuffer{ image.ImageWidth, image.ImageHeight };

	for (int frame = 1; frame <= frameCount; frame++)
	{
		std::string filename{ "picture" };
		filename.append(std::to_string(frame)).append(".bmp");

		Camera camera{ lookFrom, lookAt, vUp, vFOV, image.AspectRatio, aperture, distToFocusPlane, angleIncrement * (frame - 1)};

		Render(filename, image, camera, pixelBuffer, bvhTree, background);

		pixelBuffer.Clear();
	}

	std::cout << "\nRender time: " << sw.Elapsed() << " seconds\n";
	std::cout << image.ImageWidth << 'x' << image.ImageHeight << '\n';
	std::cout << "g_Count: " << g_Count << '\n';

	system("picture1.bmp");

}

Colour rayColour(const Ray& r, const Colour& background, const Hittable& worldObjects, int depth)
{
	HitRecord record;

	g_Count++; // function call count

	if (depth <= 0) return Colour{};

	if (worldObjects.Hit(r, 0.001, infinity, record)) // worldObjects : HittableList .Hit returns the record with lowest t value, hence closest intersection and thus the one we want to display.
	{
		Ray scattered;
		Colour attenuation;

		if (record.Material_ptr->Scatter(r, record, attenuation, scattered))
		{
			return attenuation * rayColour(scattered, background, worldObjects, depth - 1);
		}

		return Colour{};
	}

	Vector3 unitDirection = r.Direction();

	auto t = 0.5 * (unitDirection.Y() + 1);
	return (1.0 - t) * Colour { 0.8, 0.5, 0.3 } + t * background;
}

void Render(const std::string& filename, const Image& image, const Camera& camera, PixelBuffer& pixelBuffer, const Hittable& worldObjects, const Colour& background)
{

	for (int row{ image.ImageHeight - 1 }; row >= 0; --row)
	{
		std::cout << "\rScanlines remaining: " << row;

		for (int column{}; column < image.ImageWidth; ++column)
		{
			Colour c;

			for (int s{}; s < image.SamplesPerPixel; s++)
			{
				auto u = (column + RandomDouble()) / (image.ImageWidth - 1.0); // Horizontal Parametric Scalar.
				auto v = (row + RandomDouble()) / (image.ImageHeight - 1.0); // Vertical Parametric Scalar.

				Ray r{ camera.getRay(u, v) };

				c += rayColour(r, background, worldObjects, image.MaxDepth);
			}

			pixelBuffer.AddColour(c, image.SamplesPerPixel);
		}
	}

	std::cout << "\nimage write for " << filename << ": " << stbi_write_bmp(filename.data(), image.ImageWidth, image.ImageHeight, 3, pixelBuffer.Data()) << '\n' << '\n';
}


