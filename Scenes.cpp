#include <Scenes.h>

#include <Utility/Utility.h>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>
#include <Shapes/Sphere.h>

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

void Scene1(HittableList& worldObjects)
{
	auto materialGround = make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
	auto materialCenter = make_shared<Lambertian>(Colour(0.9, 0.4, 0.0));
	auto materialLeft = make_shared<Dielectric>(1.3);
	auto materialRight = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.1);

	worldObjects.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
	worldObjects.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
	worldObjects.Add(make_shared<Sphere>(Point3(-1.3, 0.0, -1.0), 0.5, materialLeft));
	//worldObjects.Add(make_shared<Sphere>(Point3(-1.8, 0.0, -1.0), -0.45, materialLeft));
	worldObjects.Add(make_shared<Sphere>(Point3(1.3, 0.0, -1.0), 0.5, materialRight));
}