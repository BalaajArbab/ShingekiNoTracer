
// Add ./Headers as an include directory.
#include "Headers/ShingekiNoTracer.h"


// Forward Declarations.
Colour rayColour(const Ray& r, const Colour& background, const Hittable& worldObjects, int depth, int threadID);
void Render(const Image& image, const Camera& camera, PixelBuffer& pixelBuffer, const Hittable& worldObjects, const Colour& background, int threadID);


int main()
{
	if (g_THREAD_COUNT <= 0) std::abort();
	InitializeRNGS();

	// Image
	double aspectRatio = 16.0 / 9.0;
	int imageHeight = 600;
	int imageWidth = static_cast<int>(imageHeight * aspectRatio);
	int samplesPerPixel = 100; // Keep this an even multiple of g_THREADCOUNT
	int maxDepth = 50;

	Image image{ aspectRatio, imageHeight, imageWidth, samplesPerPixel, maxDepth };
	image.SetSamplesAsMultipleOfTheads();

	// World / Camera
	HittableList worldObjects;
	Colour background{ 0.1, 0.4, 0.9 };
	

	Point3 lookFrom{ 0, 0, 1 };
	Point3 lookAt{ 0, 0, 0 };
	double vFOV = 90.0;

	const int scene = 4;

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
	case 2:
		Scene2(worldObjects);

		background = Colour{ 1, 1, 1 };

		lookFrom = Point3{ 13, 2, 3 };
		lookAt = Point3{ 0, 0, 0 };
		vFOV = 40.0;

		break;
	case 3:
		Zebra(worldObjects);

		aspectRatio = 16.0 / 9.0;
		imageHeight = 1080;
		imageWidth = static_cast<int>(imageHeight * aspectRatio);
		samplesPerPixel = 100;
		image = Image{ aspectRatio, imageHeight, imageWidth, samplesPerPixel, maxDepth };
		image.SetSamplesAsMultipleOfTheads();

		background = Colour{ 1, 1, 1 };

		lookFrom = Point3{ 70, 40, 80 };
		lookAt = Point3{ 0, 0, 0 };
		vFOV = 135.0;

		break;
	case 4:
		Cornell(worldObjects);

		aspectRatio = 1.0;
		imageHeight = 600;
		imageWidth = static_cast<int>(imageHeight * aspectRatio);
		samplesPerPixel = 1000;
		image = Image{ aspectRatio, imageHeight, imageWidth, samplesPerPixel, maxDepth };
		image.SetSamplesAsMultipleOfTheads();	

		background = Colour{ 0, 0, 0 };

		lookFrom = Point3{ 278, 278, -800 };
		lookAt = Point3{ 278, 278, 0 };
		vFOV = 40.0;

		break;
	case 5:
		Sandbox(worldObjects);

		lookFrom = Point3{ 60, 40, 40 }; // from zebras top right
		/*lookFrom = Point3{ 0, 0, 80 }; */// side/bodysection
		//lookFrom = Point3{ 70, 50, 0 }; // front
		//lookFrom = Point3{ 30, 60, 30 }; // top
		lookAt = Point3{ 10, 0, 0 };
		vFOV = 120.0;

		samplesPerPixel = 10;
		image = Image{ aspectRatio, imageHeight, imageWidth, samplesPerPixel, maxDepth };
		image.SetSamplesAsMultipleOfTheads();

		background = Colour{ 0.1, 0.1, 0.1 };

		break;
	}

	BVHNode bvhTree{ worldObjects };


	// Camera
	Vector3 vUp{ 0, 1, 0 };

	double aperture = 0.01;
	double distToFocusPlane = 1000.0;

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

		PixelBuffer pixelBuffers[g_THREAD_COUNT];

		for (auto& pb : pixelBuffers) pb.InitializeBuffer(image.ImageWidth, image.ImageHeight);

		std::thread threads[g_THREAD_COUNT];

		for (int t = 0; t < g_THREAD_COUNT; ++t)
		{
			threads[t] = std::thread(Render, std::ref(image), std::ref(camera), std::ref(pixelBuffers[t]), std::ref(bvhTree), std::ref(background), t);
		}

		for (auto& thread : threads) thread.join();

		PixelBuffer consolidatedPB;
		consolidatedPB.InitializeBuffer(image.ImageWidth, image.ImageHeight);

		consolidatedPB.AveragePixelBuffers(pixelBuffers, g_THREAD_COUNT, image.SamplesPerPixel);

		std::cout << "\nimage write for " << filename << ": " << stbi_write_bmp(filename.data(), image.ImageWidth, image.ImageHeight, 3, consolidatedPB.Data()) << '\n' << '\n';

		for (auto& pb : pixelBuffers) pb.Clear();
	}

	std::cout << "\nRender time: " << sw.Elapsed() << " seconds\n";
	std::cout << image.ImageWidth << 'x' << image.ImageHeight << " Samples: " << image.SamplesPerPixel << '\n';

	char ting;
	std::cin >> ting;

	system("picture1.bmp");

}

Colour rayColour(const Ray& r, const Colour& background, const Hittable& worldObjects, int depth, int threadID)
{
	HitRecord record;

	if (depth <= 0) return Colour{};

	// If the ray hits no object in the world, return background colour.
	if (!worldObjects.Hit(r, 0.001, infinity, record))
	{
		return background;
	}

	// If the ray does hit something in the world.
	Ray scattered;
	Colour attenuation{ 0, 0, 0 };
	Colour emitted = record.Material_ptr->Emitted(record.u, record.v, record.Point);

	if (!record.Material_ptr->Scatter(r, record, attenuation, scattered, threadID))
	{
		return emitted;
	}

	return emitted + attenuation * rayColour(scattered, background, worldObjects, depth - 1, threadID);
}

void Render(const Image& image, const Camera& camera, PixelBuffer& pixelBuffer, const Hittable& worldObjects, const Colour& background, int threadID)
{

	int samplesPerThread = image.SamplesPerPixel / g_THREAD_COUNT;

	for (int row{ image.ImageHeight - 1 }; row >= 0; --row)
	{
		std::cout << "\rScanlines remaining: " << row;

		for (int column{}; column < image.ImageWidth; ++column)
		{
			Colour c{ 0, 0, 0 };

			for (int s = 0; s < samplesPerThread; s++)
			{
				auto u = (column + RandomDouble()) / (image.ImageWidth - 1.0); // Horizontal Parametric Scalar.
				auto v = (row + RandomDouble()) / (image.ImageHeight - 1.0); // Vertical Parametric Scalar.

				Ray r{ camera.getRay(u, v) };

				c += rayColour(r, background, worldObjects, image.MaxDepth, threadID);

			}

			pixelBuffer.AddColour(c);
		}
	}

}



