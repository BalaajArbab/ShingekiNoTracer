#define STB_IMAGE_IMPLEMENTATION

#include <Scenes.h>

#include <Utility/Utility.h>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>
#include <Materials/Skybox.h>
#include <Materials/DiffuseLight.h>
#include <Materials/Isotropic.h>
#include <Shapes/Sphere.h>
#include <Shapes/AARects.h>
#include <Shapes/Box.h>
#include <Shapes/Cylinder.h>
#include <Shapes/Translate.h>
#include <Shapes/Rotations.h>
#include <Shapes/ConstantMedium.h>
#include <Shapes/Fractal.h>
#include <Textures/CheckerTexture.h>
#include <Textures/ImageTexture.h>
#include <Textures/RectChecker.h>


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
					colour = Clamp(colour);
					sphereMaterial = make_shared<Lambertian>(colour);
					worldObjects.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else if (chooseMaterial < 0.95)
				{
					// Metal
					Colour colour = RandomVector3(0.5, 1) - Colour{ -0.3, 0, 0.7 };
					colour = Clamp(colour);
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

void RandomSceneLights(HittableList& worldObjects)
{
	auto groundTexture = make_shared<CheckerTexture>(Colour{ 0.2, 0.2, 0.2 }, Colour{ 1, 1, 1 });
	groundTexture->SetFrequency(2);

	auto groundMaterial = make_shared<Metal>(groundTexture, 0.2);
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

				if (chooseMaterial < 0.7)
				{
					// Diffuse
					Colour colour = RandomVector3() * RandomVector3() - Colour{ -0.3, 0, 0.7 };
					colour = Clamp(colour);
					sphereMaterial = make_shared<Lambertian>(colour);
					worldObjects.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else if (chooseMaterial < 0.90)
				{
					// Metal
					Colour colour = RandomVector3(0.5, 1) - Colour{ -0.3, 0, 0.7 };
					colour = Clamp(colour);
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

	auto lambertianMat = make_shared<Lambertian>(Colour{ 0.3, 0.294, 1.0 });
	worldObjects.Add(make_shared<Sphere>(Point3{ -4, 1, 0 }, 1.0, lambertianMat));

	auto metalMat = make_shared<Metal>(Colour{ 0.8, 0.6, 0.1 }, 0.0);
	worldObjects.Add(make_shared<Sphere>(Point3{ 4, 1, 0 }, 1.0, metalMat));

	auto lightMat = make_shared<DiffuseLight>(Colour{ 20.0, 14.0, 5.0 });
	worldObjects.Add(make_shared<Sphere>(Point3{ 0, 100, 0 }, 25.0, lightMat));

	auto spaceTexture = make_shared<ImageTexture>("images/space.jpg");
	auto backgroundMat = make_shared<Skybox>(spaceTexture);

	auto front = make_shared<XYRect>(-800, 800, -200, 500, 500, backgroundMat);
	auto back = make_shared<XYRect>(-800, 800, -200, 500, -500, backgroundMat);

	auto top = make_shared<XZRect>(-800, 800, -500, 500, 500, backgroundMat);

	auto left = make_shared<YZRect>(-500, 500, -500, 500, -800, backgroundMat);
	auto right = make_shared<YZRect>(-500, 500, -500, 500, 800, backgroundMat);

	worldObjects.Add(front);
	worldObjects.Add(back);
	worldObjects.Add(top);
	worldObjects.Add(left);
	worldObjects.Add(right);
}

void Zebra(HittableList& worldObjects)
{
	// Skybox
	auto skyFront = make_shared<ImageTexture>("images/front.jpg");
	auto matFront = make_shared<Skybox>(skyFront);
	auto skyBack = make_shared <ImageTexture>("images/back.jpg");
	auto matBack = make_shared<Skybox>(skyBack);

	auto skyLeft = make_shared<ImageTexture>("images/left.jpg");
	auto matLeft = make_shared<Skybox>(skyLeft);
	auto skyRight = make_shared<ImageTexture>("images/right.jpg");
	auto matRight = make_shared<Skybox>(skyRight);

	auto skyTop = make_shared<ImageTexture>("images/top.jpg");
	auto matTop = make_shared<Skybox>(skyTop);
	auto skyBottom = make_shared<ImageTexture>("images/bottom.jpg");
	auto matBottom = make_shared<Skybox>(skyBottom);

	auto stripes = make_shared<ImageTexture>("images/zebra.jpg");
	auto stripesMat = make_shared<Skybox>(stripes);

	auto skyboxObjects = make_shared<HittableList>();

	auto xyRect1 = make_shared<XYRect>(-5000, 5000, -5000, 5000, -5000, matFront);
	auto xyRect2 = make_shared<XYRect>(-5000, 5000, -5000, 5000, 5000, matBack);

	auto yzRect1 = make_shared<YZRect>(-5000, 5000, -5000, 5000, -5000, matLeft);
	auto yzRect2 = make_shared<YZRect>(-5000, 5000, -5000, 5000, 5000, matRight);

	auto xzRect1 = make_shared<XZRect>(-5000, 5000, -5000, 5000, 5000, matTop);
	auto xzRect2 = make_shared<XZRect>(-5000, 5000, -5000, 5000, -5000, matBottom);

	/*auto xyRect1 = make_shared<XYRect>(-5000, 5000, -5000, 5000, -5000, stripesMat);
	auto xyRect2 = make_shared<XYRect>(-5000, 5000, -5000, 5000, 5000, stripesMat);

	auto yzRect1 = make_shared<YZRect>(-5000, 5000, -5000, 5000, -5000, stripesMat);
	auto yzRect2 = make_shared<YZRect>(-5000, 5000, -5000, 5000, 5000, stripesMat);

	auto xzRect1 = make_shared<XZRect>(-5000, 5000, -5000, 5000, 5000, stripesMat);
	auto xzRect2 = make_shared<XZRect>(-5000, 5000, -5000, 5000, -5000, stripesMat);*/


	skyboxObjects->Add(xyRect1);
	skyboxObjects->Add(xyRect2);

	skyboxObjects->Add(yzRect1);
	skyboxObjects->Add(yzRect2);

	skyboxObjects->Add(xzRect1);
	skyboxObjects->Add(xzRect2);

	// Floor
	auto checkerTexture = make_shared<CheckerTexture>(Colour{ 0.2, 0.2, 0.2 }, Colour{ 0.8, 0.8, 0.8 });
	checkerTexture->SetFrequency(2);

	auto checkerMat = make_shared<Metal>(checkerTexture, 0.2);
	auto floor = make_shared<Sphere>(Point3{ 0, -10030, 0 }, 10000, checkerMat);

	// Materials

	auto body = make_shared<Metal>(Colour(1.0, 1.0, 1.0), 0.0);

	auto hairtail = make_shared<Lambertian>(Colour{});

	auto eyes = make_shared<Lambertian>(Colour{});

	auto light = make_shared<DiffuseLight>(Colour{ 15, 15, 15 });
	
	// Zebra

	auto zebra = make_shared<HittableList>();

	shared_ptr<Hittable> cylinderBody = make_shared<Cylinder>(0, 80, 15, body);
	cylinderBody = make_shared<RotateY>(cylinderBody, 90);
	cylinderBody = make_shared<Translate>(cylinderBody, Vector3{ -40, 15, 0 });

	shared_ptr<Hittable> cylinderHindLeg1 = make_shared<Cylinder>(0, 50, 5, body);
	cylinderHindLeg1 = make_shared<RotateX>(cylinderHindLeg1, 90);
	cylinderHindLeg1 = make_shared<Translate>(cylinderHindLeg1, Vector3{ -30, 20, 10 });

	shared_ptr<Hittable> cylinderHindLeg2 = make_shared<Cylinder>(0, 50, 5, body);
	cylinderHindLeg2 = make_shared<RotateX>(cylinderHindLeg2, 90);
	cylinderHindLeg2 = make_shared<Translate>(cylinderHindLeg2, Vector3{ -30, 20, -10 });

	shared_ptr<Hittable> cylinderFrontLeg1 = make_shared<Cylinder>(0, 50, 5, body);
	cylinderFrontLeg1 = make_shared<RotateX>(cylinderFrontLeg1, 90);
	cylinderFrontLeg1 = make_shared<Translate>(cylinderFrontLeg1, Vector3{ 30, 20, 10 });

	shared_ptr<Hittable> cylinderFrontLeg2 = make_shared<Cylinder>(0, 50, 5, body);
	cylinderFrontLeg2 = make_shared<RotateX>(cylinderFrontLeg2, 90);
	cylinderFrontLeg2 = make_shared<Translate>(cylinderFrontLeg2, Vector3{ 30, 20, -10 });

	shared_ptr<Hittable> behindRump = make_shared<Sphere>(Point3{ -26, 15, 0 }, 20.5, body);
	shared_ptr<Hittable> frontRump = make_shared<Sphere>(Point3{ 30, 15, 0 }, 18.2, body);
	shared_ptr<Hittable> belly = make_shared<Sphere>(Point3{ 4, 13.2, 0 }, 16.9, body);

	shared_ptr<Hittable> tailOne = make_shared<Sphere>(Point3{ -52, 15, 0 }, 7, hairtail);
	shared_ptr<Hittable> tailTwo = make_shared<Sphere>(Point3{ -52, 4.5, 0 }, 5, hairtail);
	shared_ptr<Hittable> tailThree = make_shared<Sphere>(Point3{ -52, -3, 0 }, 4, hairtail);
	shared_ptr<Hittable> tailFour = make_shared<Sphere>(Point3{ -52, -9, 0 }, 3, hairtail);
	shared_ptr<Hittable> tailFive = make_shared<Sphere>(Point3{ -52, -13.5, 0 }, 2, hairtail);
	shared_ptr<Hittable> tailSix = make_shared<Sphere>(Point3{ -52, -17.5, 0 }, 2, hairtail);
	shared_ptr<Hittable> tailSeven = make_shared<Sphere>(Point3{ -52, -20.5, 0 }, 1, hairtail);

	shared_ptr<Hittable> cylinderNeck = make_shared<Cylinder>(0, 20, 6, body);
	cylinderNeck = make_shared<RotateX>(cylinderNeck, 90);
	cylinderNeck = make_shared<RotateZ>(cylinderNeck, -45);
	cylinderNeck = make_shared<Translate>(cylinderNeck, Vector3{ 50, 40, 0 });

	shared_ptr<Hittable> face = make_shared<Sphere>(Point3{ 52, 43, 0 }, 7, body);
	shared_ptr<Hittable> eye1 = make_shared<Sphere>(Point3{ 56, 45, 5 }, 1, eyes);
	shared_ptr<Hittable> eye2 = make_shared<Sphere>(Point3{ 56, 45, -5 }, 1, eyes);


	shared_ptr<Hittable> snout = make_shared<Cylinder>(0, 10, 2.5, body);
	snout = make_shared<RotateX>(snout, 90);
	snout = make_shared<RotateZ>(snout, 45);
	snout = make_shared<Translate>(snout, Vector3{ 56, 41, 0 });

	shared_ptr<Hittable> hairOne = make_shared<Sphere>(Point3{ 48, 49, 0 }, 4, hairtail);
	shared_ptr<Hittable> hairTwo = make_shared<Sphere>(Point3{ 45, 46, 0 }, 3, hairtail);
	shared_ptr<Hittable> hairThree = make_shared<Sphere>(Point3{ 42, 43, 0 }, 3, hairtail);
	shared_ptr<Hittable> hairFour = make_shared<Sphere>(Point3{ 39, 40, 0 }, 3, hairtail);
	shared_ptr<Hittable> hairFive = make_shared<Sphere>(Point3{ 36, 37, 0 }, 3, hairtail);
	shared_ptr<Hittable> hairSix = make_shared<Sphere>(Point3{ 34, 35, 0 }, 2, hairtail);

	zebra->Add(cylinderBody);
	zebra->Add(cylinderHindLeg1);
	zebra->Add(cylinderHindLeg2);
	zebra->Add(cylinderFrontLeg1);
	zebra->Add(cylinderFrontLeg2);
	zebra->Add(behindRump);
	zebra->Add(frontRump);
	zebra->Add(belly);
	zebra->Add(tailOne);
	zebra->Add(tailTwo);
	zebra->Add(tailThree);
	zebra->Add(tailFour);
	zebra->Add(tailFive);
	zebra->Add(tailSix);
	zebra->Add(tailSeven);
	zebra->Add(cylinderNeck);
	zebra->Add(face);
	zebra->Add(eye1);
	zebra->Add(eye2);
	zebra->Add(snout);
	zebra->Add(hairOne);
	zebra->Add(hairTwo);
	zebra->Add(hairThree);
	zebra->Add(hairFour);
	zebra->Add(hairFive);
	zebra->Add(hairSix);

	worldObjects.Add(zebra);
	worldObjects.Add(skyboxObjects);
	worldObjects.Add(floor);

}

void Cornell(HittableList& worldObjects)
{
	auto cornellWalls = make_shared<HittableList>();

	auto red = make_shared<Lambertian>(Colour{ 0.65, 0.05, 0.05 });
	auto white = make_shared<Lambertian>(Colour{ 0.73, 0.73, 0.73 });
	auto green = make_shared<Lambertian>(Colour{ 0.12, 0.45, 0.15 });
	auto light = make_shared<DiffuseLight>(Colour{ 3, 3, 3 });

	auto mirror = make_shared<Metal>(Colour{ 1, 1, 1 }, 0.0);
	auto mirror2 = make_shared<Metal>(Colour{ 0.73, 0.73, 0.73 }, 0.2);

	cornellWalls->Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
	cornellWalls->Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
	cornellWalls->Add(make_shared<XZRect>(200, 400, 200, 360, 554, light));
	cornellWalls->Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
	cornellWalls->Add(make_shared<XZRect>(0, 555, 0, 555, 555, white));
	cornellWalls->Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

	worldObjects.Add(cornellWalls);

	shared_ptr<Hittable> box1 = make_shared<Box>(Point3{ 0, 0, 0 }, Point3{ 165, 330, 165 }, white, std::bitset<6>{ 0b000001 }); // taller, left
	box1 = make_shared<RotateY>(box1, 15);
	box1 = make_shared<Translate>(box1, Vector3{ 265, 0, 295 });

	shared_ptr<Hittable> box2 = make_shared<Box>(Point3{ 0, 0, 0 }, Point3{ 165, 165, 165 }, white); // shorter, right
	box2 = make_shared<RotateY>(box2, -18);
	box2 = make_shared<Translate>(box2, Vector3{ 130, 0, 65 });

	shared_ptr<Hittable> ball = make_shared<Sphere>(Point3{ 170, 80, 105 }, 80, mirror2);

	auto clouds = make_shared<ImageTexture>("yellowcloud_bk.jpg");
	auto matClouds = make_shared<Skybox>(clouds);
	shared_ptr<Hittable> oppositeWall = make_shared<XYRect>(-5500, 6000, -5500, 6000, -801, matClouds);

	worldObjects.Add(box1);
	//worldObjects.Add(box2);
	worldObjects.Add(ball);

	worldObjects.Add(oppositeWall);
}

void Aesthetic(HittableList& worldObjects)
{

}

void Sasageyo(HittableList& worldObjects)
{
	auto wofImage = make_shared<ImageTexture>("images/wof.jpg");
	auto materialMainSphere = make_shared<Lambertian>(wofImage);
	shared_ptr<Hittable> wofSphere = make_shared<Sphere>(Point3{ 0, 0, 0 }, 5, materialMainSphere);
	wofSphere = make_shared<RotateY>(wofSphere, 90);

	auto metalMat = make_shared<Metal>(Colour{ 0.73, 0.73, 0.73 }, 0.1);
	auto metalMat2 = make_shared<Metal>(Colour{ 0.73, 0.73, 0.73 }, 0.2);

	for (int i = 0; i < 12; ++i)
	{
		shared_ptr<Hittable> sphere = make_shared<Sphere>(Point3{ -15, 0, 0 }, 3, metalMat2);
		sphere = make_shared<RotateZ>(sphere, i * (360 / 12));

		worldObjects.Add(sphere);
	}

	for (int i = 0; i < 12; ++i)
	{
		shared_ptr<Hittable> sphere = make_shared<Sphere>(Point3{ 25, 0, -5 }, 2.5, metalMat);
		sphere = make_shared<RotateZ>(sphere, i * (360 / 12));

		worldObjects.Add(sphere);
	}

	worldObjects.Add(wofSphere);


	// Floor
	auto checkerTexture = make_shared<CheckerTexture>(Colour{ 0.2, 0.2, 0.2 }, Colour{ 0.8, 0.8, 0.8 });
	checkerTexture->SetFrequency(2);

	auto checkerMat = make_shared<Metal>(checkerTexture, 0.2);
	auto floor = make_shared<Sphere>(Point3{ 0, -10030, 0 }, 10000, checkerMat);

	worldObjects.Add(floor);


	// Skybox
	auto skyFront = make_shared<ImageTexture>("images/front.jpg");
	auto matFront = make_shared<Skybox>(skyFront);
	auto skyBack = make_shared <ImageTexture>("images/back.jpg");
	auto matBack = make_shared<Skybox>(skyBack);

	auto skyLeft = make_shared<ImageTexture>("images/left.jpg");
	auto matLeft = make_shared<Skybox>(skyLeft);
	auto skyRight = make_shared<ImageTexture>("images/right.jpg");
	auto matRight = make_shared<Skybox>(skyRight);

	auto skyTop = make_shared<ImageTexture>("images/top.jpg");
	auto matTop = make_shared<Skybox>(skyTop);
	auto skyBottom = make_shared<ImageTexture>("images/bottom.jpg");
	auto matBottom = make_shared<Skybox>(skyBottom);

	auto skyboxObjects = make_shared<HittableList>();

	auto xyRect1 = make_shared<XYRect>(-5000, 5000, -5000, 5000, -5000, matFront);
	auto xyRect2 = make_shared<XYRect>(-5000, 5000, -5000, 5000, 5000, matBack);

	auto yzRect1 = make_shared<YZRect>(-5000, 5000, -5000, 5000, -5000, matLeft);
	auto yzRect2 = make_shared<YZRect>(-5000, 5000, -5000, 5000, 5000, matRight);

	auto xzRect1 = make_shared<XZRect>(-5000, 5000, -5000, 5000, 5000, matTop);
	auto xzRect2 = make_shared<XZRect>(-5000, 5000, -5000, 5000, -5000, matBottom);

	skyboxObjects->Add(xyRect1);
	skyboxObjects->Add(xyRect2);

	skyboxObjects->Add(yzRect1);
	skyboxObjects->Add(yzRect2);

	skyboxObjects->Add(xzRect1);
	skyboxObjects->Add(xzRect2);

	worldObjects.Add(skyboxObjects);
}

void KekWorld(HittableList& worldObjects)
{

	auto kek1 = make_shared<ImageTexture>("images/KEK1.png");
	auto kek2 = make_shared<ImageTexture>("images/KEK2.png");
	auto kek3 = make_shared<ImageTexture>("images/KEK3.png");
	auto kek4 = make_shared<ImageTexture>("images/KEK4.png");

	auto kek1m = make_shared<Lambertian>(kek1);
	auto kek2m = make_shared<Lambertian>(kek2);
	auto kek3m = make_shared<Lambertian>(kek3);
	auto kek4m = make_shared<Lambertian>(kek4);


	for (int x = -11; x < 11; x += 5)
	{
		for (int y = 0; y < 22; y += 5)
		{
			for (int z = -11; z < 11; z += 5)
			{
				Vector3 center{ 3 * x + RandomDouble(), 3 * y + RandomDouble(), 4 * z + RandomDouble()};
				double radius = RandomDouble(1.0, 4.0);

				int kek = RandomInteger(1, 4);
				shared_ptr<Material> kekMaterial;

				switch (kek)
				{
				case 1:
					kekMaterial = kek1m;
					break;
				case 2:
					kekMaterial = kek2m;
					break;
				case 3:
					kekMaterial = kek3m;
					break;
				case 4:
					kekMaterial = kek4m;
					break;
				}

				worldObjects.Add(make_shared<Sphere>(center, radius, kekMaterial));

			}
		}
	}

	
}

void DragonCurve(HittableList& worldObjects)
{
	auto background = make_shared<ImageTexture>("images/TwilightStrand.jpg");
	auto backgroundMat = make_shared<Skybox>(background);
	auto backgroundRect = make_shared<XYRect>(-3000, 3000, -3000, 3000, -1500, backgroundMat);

	DragonCurveGenerator dragonCurve{ 16, worldObjects };

	worldObjects.Add(backgroundRect);
}

void CornellSmoke(HittableList& worldObjects)
{
	auto cornellWalls = make_shared<HittableList>();

	auto red = make_shared<Lambertian>(Colour{ 0.65, 0.05, 0.05 });
	auto white = make_shared<Lambertian>(Colour{ 0.73, 0.73, 0.73 });
	auto green = make_shared<Lambertian>(Colour{ 0.12, 0.45, 0.15 });
	auto light = make_shared<DiffuseLight>(Colour{ 3, 3, 3 });

	auto mirror = make_shared<Metal>(Colour{ 1, 1, 1 }, 0.0);
	auto mirror2 = make_shared<Metal>(Colour{ 0.73, 0.73, 0.73 }, 0.2);

	cornellWalls->Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
	cornellWalls->Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
	cornellWalls->Add(make_shared<XZRect>(113, 443, 127, 432, 554, light));
	cornellWalls->Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
	cornellWalls->Add(make_shared<XZRect>(0, 555, 0, 555, 555, white));
	cornellWalls->Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

	worldObjects.Add(cornellWalls);

	shared_ptr<Hittable> box1 = make_shared<Box>(Point3{ 0, 0, 0 }, Point3{ 165, 330, 165 }, white, std::bitset<6>{ 0b000000 }); // taller, left
	box1 = make_shared<RotateY>(box1, 15);
	box1 = make_shared<Translate>(box1, Vector3{ 265, 0, 295 });

	shared_ptr<Hittable> box2 = make_shared<Box>(Point3{ 0, 0, 0 }, Point3{ 165, 165, 165 }, white); // shorter, right
	box2 = make_shared<RotateY>(box2, -18);
	box2 = make_shared<Translate>(box2, Vector3{ 130, 0, 65 });

	shared_ptr<Hittable> ball = make_shared<Sphere>(Point3{ 170, 80, 105 }, 80, white);

	auto clouds = make_shared<ImageTexture>("yellowcloud_bk.jpg");
	auto matClouds = make_shared<Skybox>(clouds);
	shared_ptr<Hittable> oppositeWall = make_shared<XYRect>(-5500, 6000, -5500, 6000, -801, matClouds);

	box1 = make_shared<ConstantMedium>(box1, 0.01, Colour{ 0, 0, 0 });
	ball = make_shared<ConstantMedium>(ball, 0.01, Colour{ 1, 1, 1 });

	worldObjects.Add(box1);
	//worldObjects.Add(box2);
	worldObjects.Add(ball);

	worldObjects.Add(oppositeWall);
}

void CornellInvisWalls(HittableList& worldObjects)
{
	// Textures / Materials
	auto red = make_shared<Lambertian>(Colour{ 0.65, 0.05, 0.05 });
	auto white = make_shared<Lambertian>(Colour{ 0.82, 0.82, 0.82 });
	auto green = make_shared<Lambertian>(Colour{ 0.12, 0.45, 0.15 });
	auto blue = make_shared<Lambertian>(Colour{ 0.015, 0.109, 0.21 });
	auto light = make_shared<DiffuseLight>(Colour{ 15, 15, 15 });

	auto dielectric = make_shared<Dielectric>(1.5);

	auto mirror = make_shared<Metal>(Colour{ 0.73, 0.73, 0.73 }, 0.0);

	auto floorTexture = make_shared<RectChecker>(Colour{ 0.73, 0.73, 0.73 }, Colour{ 0.015, 0.109, 0.21 });
	floorTexture->SetFrequency(8);
	auto floorMat = make_shared<Metal>(floorTexture, 0.0);

	// Cornell Structure
	auto cornellWalls = make_shared<HittableList>();

	// Right
	auto rightWall = make_shared<YZRect>(0, 555, -100, 800, -400, red);
	rightWall->MakeInvisible();

	cornellWalls->Add(rightWall);

	// Left
	cornellWalls->Add(make_shared<YZRect>(0, 555, -100, 555, 555, green));
	
	// Top
	cornellWalls->Add(make_shared<XZRect>(-400, 555, -100, 800, 555, white));

	// Floor
	cornellWalls->Add(make_shared<XZRect>(-400, 555, -100, 800, 0, floorMat));

	// Back
	cornellWalls->Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));
	cornellWalls->Add(make_shared<YZRect>(0, 555, 555, 800, 0, white));
	cornellWalls->Add(make_shared<XYRect>(-400, 0, 0, 555, 800, white));

	cornellWalls->Add(make_shared<Box>(Point3{ -400, 300, 750 }, Point3{ 0, 400, 800 }, white));

	// Opposite Wall
	auto oppositeWall = make_shared <XYRect>(-400, 555, 0, 555, -100, white);
	oppositeWall->MakeInvisible();

	cornellWalls->Add(oppositeWall);

	// Light
	cornellWalls->Add(make_shared<Box>(Point3{ 150, 525, 150 }, Point3{ 420, 555, 380 }, white));
	cornellWalls->Add(make_shared<XZRect>(150, 420, 150, 380, 524, light));

	worldObjects.Add(cornellWalls);

	// Objects
	shared_ptr<Hittable> ball = make_shared<Sphere>(Point3{ -70, 110, 250 }, 110, mirror);

	shared_ptr<Hittable> ball2 = make_shared<Sphere>(Point3{ -300, 35, 0 }, 35, white);

	shared_ptr<Hittable> ball3 = make_shared<Sphere>(Point3{ 250, 250, 100 }, 80, dielectric);

	cornellWalls->Add(make_shared<Box>(Point3{ 235, 0, 85 }, Point3{ 265, 170, 115 }, blue));
	
	worldObjects.Add(ball);
	worldObjects.Add(ball2);
	worldObjects.Add(ball3);

}