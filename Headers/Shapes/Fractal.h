#ifndef FRACTAL_H
#define FRACTAL_H

#include <Renderer/Hittable.h>
#include <Shapes/AARects.h>
#include <Shapes/Translate.h>
#include <Shapes/Rotations.h>

// Not really fractals, at least in the end product/shape formed. But similar concept.

inline void SemiFractalXY(HittableList& worldObjects, double p1, double p2, double q1, double q2, double initialPFactor, double initialQFactor, int depth, double z, shared_ptr<Material> mat)
{
	if (depth != 0)
	{
		double pMid = fabs(p1 - p2) * initialPFactor;
		double qMid = fabs(q1 - q2) * initialQFactor;

		SemiFractalXY(worldObjects, p1, p1 + pMid, q1, q1 + qMid, RandomDouble(0.2, 0.7), RandomDouble(0.2, 0.7), depth - 1, z, mat);
		SemiFractalXY(worldObjects, p1, p1 + pMid, q1 + qMid, q2, RandomDouble(0.2, 0.7), RandomDouble(0.2, 0.7), depth - 1, z, mat);

		SemiFractalXY(worldObjects, p1 + pMid, p2, q1, q1 + qMid, RandomDouble(0.2, 0.7), RandomDouble(0.2, 0.7), depth - 1, z, mat);
		SemiFractalXY(worldObjects, p1 + pMid, p2, q1 + qMid, q2, RandomDouble(0.2, 0.7), RandomDouble(0.2, 0.7), depth - 1, z, mat);
	}
	else
	{
		double rotate = sin(p1 * 33) + cos(p2 * 41) + sin(q1 * -35) + cos(q2 * -37);
		rotate /= 4;

		int rotateDegrees = RadiansToDegrees(asin(rotate)) / 2.5;

		double xMid = (p1 + p2) / 2.0;
		double yMid = (q1 + q2) / 2.0;

		shared_ptr<Hittable> rect = make_shared<XYRect>(p1, p2, q1, q2, 0, mat);
		rect = make_shared<Translate>(rect, Vector3{ -xMid, -yMid, 0 });
		rect = make_shared<RotateX>(rect, rotateDegrees);
		rect = make_shared<Translate>(rect, Vector3{ xMid, yMid, z });

		std::cout << rotateDegrees << "\n";
		worldObjects.Add(rect);
	}
}

#endif
