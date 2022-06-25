#ifndef RAY_H
#define RAY_H

#include <Math/Vector3.h>

class Ray
{
private:
	Point3 m_origin;
	Vector3 m_direction;

public:
	Ray() = default;

	Ray(const Point3& origin, const Vector3& direction)
		: m_origin{ origin }, m_direction{ UnitVector(direction) }
	{}

	Point3 Origin() const 
	{ 
		return m_origin; 
	}

	Vector3 Direction() const
	{
		return m_direction;
	}

	Point3 At(double t) const
	{
		return m_origin + (m_direction * t);
	}

};

#endif
