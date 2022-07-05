#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include <Renderer/HittableList.h>
#include <Shapes/Sphere.h>
#include <Shapes/AARects.h>
#include <Materials/Lambertian.h>
#include <Materials/DiffuseLight.h>
#include <Textures/ImageTexture.h>

class DragonCurveGenerator
{
private:
	enum Direction
	{
		Up,
		Down,
		Left,
		Right
	};

public:
	DragonCurveGenerator(int iterations, HittableList& worldObjects)
		: m_iterations{ iterations }
	{
		std::string moves{ "F" };

		LSystem(iterations, moves);

		Point3 point{ 0, 0, 0 };
		Direction orientation = Up;

		m_points.reserve(5000);
		m_points.push_back(point);

		int iteration = 0;
		int pointCount = 1;
		int lastIterPointCount{ };

		for (char move : moves)
		{
			bool pointAdded = false;
			switch (move)
			{
			case 'F':
				point = Move(orientation, point, iteration);
				m_points.push_back(point);
				++pointCount;
				pointAdded = true;

				break;
			case 'H':
				point = Move(orientation, point, iteration);
				m_points.push_back(point);
				++pointCount;
				pointAdded = true;

				break;
			case '-':
				orientation = Turn(orientation, '-');

				break;
			case '+':
				orientation = Turn(orientation, '+');

				break;
			}

			if (pointAdded && pointCount == 2)
			{
				++iteration;
				lastIterPointCount = 2;
			}
			else if (pointAdded && (pointCount == (lastIterPointCount + pow(2, iteration - 1))))
			{
				++iteration;
				lastIterPointCount = pointCount;
			}
		}

		auto chaosOrb = make_shared<ImageTexture>("images/chaos.png");
		auto chaosOrbMat = make_shared<DiffuseLight>(chaosOrb);

		auto eternalOrb = make_shared<ImageTexture>("images/eternal.png");
		auto eternalOrbMat = make_shared<DiffuseLight>(eternalOrb);

		for (auto& p : m_points)
		{
			shared_ptr<Material> mat;

			if (p.Z() < 16) mat = chaosOrbMat;
			else mat = eternalOrbMat;

			auto pointRect = make_shared<XYRect>(p.X(), p.X() + 1, p.Y(), p.Y() + 1, 0, mat);

			worldObjects.Add(pointRect);
		}

		std::cout << "Dragon Curve generated.\n";
	}
	
private:
	std::vector<Point3> m_points;
	int m_iterations;

	static void LSystem(int iterations, std::string& str)
	{
		for (int i = 0; i < iterations; ++i)
		{
			std::string iterStr{ };

			for (char c : str)
			{
				iterStr += Production(c);
			}

			str = iterStr;
		}

	}

	static std::string Production(char c)
	{
		switch (c)
		{
		case 'F':
			return "F-H";
			break;
		case 'H':
			return "F+H";
			break;
		default:
			return std::string{ c };
			break;
		}
	}

	static Direction Turn(Direction orientation, char turn)
	{
		switch (turn)
		{
		case '-':
			switch (orientation)
			{
			case Up:
				return Left;
				break;
			case Left:
				return Down;
				break;
			case Down:
				return Right;
				break;
			case Right:
				return Up;
				break;
			}

		case '+':
			switch (orientation)
			{
			case Up:
				return Right;
				break;
			case Left:
				return Up;
				break;
			case Down:
				return Left;
				break;
			case Right:
				return Down;
				break;
			}
		}

	}

	static Vector3 Move(Direction orientation, const Point3& point, double iteration)
	{
		switch (orientation)
		{
		case Up:
			return Vector3{ point.X(), point.Y() + 1, iteration };
			break;
		case Down:
			return Vector3{ point.X(), point.Y() - 1, iteration };
			break;
		case Left:
			return Vector3{ point.X() - 1, point.Y(), iteration };
			break;
		case Right:
			return Vector3{ point.X() + 1, point.Y(), iteration };
			break;
		}

	}

};

#endif
