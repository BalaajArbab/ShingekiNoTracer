#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

// Add ./Headers as an include directory.
#include <ShingekiNoTracer.h>

// Forward Declarations.
Colour rayColour(const Ray& r, const Hittable& worldObjects, int depth);
void Render(const std::string& filename, const Image& image, const Camera& camera, PixelBuffer& pixelBuffer, HittableList worldObjects);
void RandomScene(HittableList& worldObjects);

int main()
{
	// Image
	constexpr double aspectRatio = 16.0 / 9.0;
	constexpr int imageHeight = 600;
	constexpr int imageWidth = static_cast<int>(imageHeight * aspectRatio);
	constexpr int samplesPerPixel = 100;
	constexpr int maxDepth = 50;

	Image image{ aspectRatio, imageHeight, imageWidth, samplesPerPixel, maxDepth };


	//World
	HittableList worldObjects;

	/*auto materialGround = make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
	auto materialCenter = make_shared<Lambertian>(Colour(1.0, 0.0, 0.0));
	auto materialLeft = make_shared<Dielectric>(1.5);
	auto materialRight = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.2);

	worldObjects.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	worldObjects.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
	worldObjects.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	worldObjects.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, materialLeft));
	worldObjects.Add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));*/

	RandomScene(worldObjects);


	// Camera

	Point3 lookFrom{ 16, 3, 3 };
	Point3 lookAt{ 0, 0, 0 };
	Vector3 vUp{ 0, 1, 0 };
	double vFOV = 20.0;

	double aperture = 0.1;
	double distToFocusPlane = 100.0;

	//double distToFocusPlane = (lookFrom - lookAt).Magnitude();
	//Camera camera{ lookFrom, lookAt, vUp, vFOV, image.AspectRatio, aperture, distToFocusPlane, 0 };


	// Render

	std::int32_t frameCount = 60;
	double angleIncrement = 360 / frameCount;

	Stopwatch sw;
	sw.Start();

	PixelBuffer pixelBuffer{ image.ImageWidth, image.ImageHeight };

	for (int frame = 1; frame <= frameCount; frame++)
	{
		std::string filename{ "picture" };
		filename.append(std::to_string(frame)).append(".bmp");

		Camera camera{ lookFrom, lookAt, vUp, vFOV, image.AspectRatio, aperture, distToFocusPlane, angleIncrement * (frame - 1)};

		Render(filename, image, camera, pixelBuffer, worldObjects);

		pixelBuffer.Clear();
	}

	std::cout << "\nRender time: " << sw.Elapsed() << " seconds\n";
	std::cout << image.ImageWidth << 'x' << image.ImageHeight << '\n';

	system("picture1.bmp");


}

Colour rayColour(const Ray& r, const Hittable& worldObjects, int depth)
{
	HitRecord record;

	if (depth <= 0) return Colour{};

	if (worldObjects.Hit(r, 0.001, infinity, record)) // worldObjects : HittableList .Hit returns the record with lowest t value, hence closest intersection and thus the one we want to display.
	{
		Ray scattered;
		Colour attenuation;

		if (record.Material_ptr->Scatter(r, record, attenuation, scattered))
		{
			return attenuation * rayColour(scattered, worldObjects, depth - 1);
		}

		return Colour{};
	}

	Vector3 unitDirection = UnitVector(r.Direction());

	auto t = 0.5 * (unitDirection.Y() + 1);
	return (1.0 - t) * Colour { 1.0, 1.0, 1.0 } + t * Colour{ 1.0, 0.5, 0.2 };
}

void Render(const std::string& filename, const Image& image, const Camera& camera, PixelBuffer& pixelBuffer, HittableList worldObjects)
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

				c += rayColour(r, worldObjects, image.MaxDepth);
			}

			pixelBuffer.AddColour(c, image.SamplesPerPixel);
		}
	}

	std::cout << "\nimage write for " << filename << ": " << stbi_write_bmp(filename.data(), image.ImageWidth, image.ImageHeight, 3, pixelBuffer.Data()) << '\n' << '\n';
}

void RandomScene(HittableList& worldObjects)
{
	auto groundMaterial = make_shared<Lambertian>(Colour{ 0.9, 0.5, 0.5 });
	worldObjects.Add(make_shared<Sphere>(Point3{ 0, -1000, 0 }, 1000, groundMaterial));

	auto dielectricMat = make_shared <Dielectric>(1.5);

	for (int a = -11; a < 11; a += 2)
	{
		for (int b = -11; b < 11; b += 2)
		{
			auto chooseMaterial = RandomDouble();

			Point3 center{ a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble() };

			if ((center - Point3(4, 0.2, 0)).Magnitude() > 0.9)
			{
				shared_ptr<Material> sphereMaterial;

				if (chooseMaterial < 0.8)
				{
					// Diffuse
					Colour colour = RandomVector3() * RandomVector3() - Colour{ -0.3, 0, 0.7 };
					sphereMaterial = make_shared<Lambertian>(colour);
					worldObjects.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else if (chooseMaterial < 0.95)
				{
					// Metal
					Colour colour = RandomVector3(0.5, 1) - Colour{ -0.3, 0, 0.7 };
					double fuzz = RandomDouble(0, 0.5);
					sphereMaterial = make_shared<Metal>(colour, fuzz);
					worldObjects.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else
				{
					worldObjects.Add(make_shared<Sphere>(center, 0.2, dielectricMat));
				}
			}
		}
	}

	worldObjects.Add(make_shared<Sphere>(Point3{ 0, 1, 0 }, 1.0, dielectricMat));

	auto lambertianMat = make_shared<Lambertian>(Colour{ 1.0, 0.4, 0.0 });
	worldObjects.Add(make_shared<Sphere>(Point3{ -4, 1, 0 }, 1.0, lambertianMat));

	auto metalMat = make_shared<Metal>(Colour{ 0.8, 0.6, 0.1 }, 0.0);
	worldObjects.Add(make_shared<Sphere>(Point3{ 4, 1, 0 }, 1.0, metalMat));

}

