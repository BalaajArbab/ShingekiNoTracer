#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>
#include <Utility/Utility.h>

using std::sqrt;

class Vector3
{
private:
	double m_v[3]{ 0.0, 0.0, 0.0 };

public:
	Vector3() = default;

	Vector3(double x, double y, double z) : m_v{ x, y, z }
	{

	}

	double X() const { return m_v[0]; }
	double Y() const { return m_v[1]; }
	double Z() const { return m_v[2]; }

	Vector3 operator-() const { return Vector3{ -m_v[0], -m_v[1], -m_v[2] }; }
	double operator[](int i) const { return m_v[i]; }
	double& operator[](int i) { return m_v[i]; }

	Vector3& operator+=(const Vector3& u)
	{
		m_v[0] += u[0];
		m_v[1] += u[1];
		m_v[2] += u[2];

		return *this;
	}

	Vector3& operator*=(const double t)
	{
		m_v[0] *= t;
		m_v[1] *= t;
		m_v[2] *= t;

		return *this;
	}

	Vector3& operator/=(const double t)
	{
		return *this *= (1 / t);
	}

	double Magnitude() const
	{
		return sqrt(MagnitudeSquared());
	}

	double MagnitudeSquared() const
	{
		return m_v[0] * m_v[0] + m_v[1] * m_v[1] + m_v[2] * m_v[2];
	}

	// Return true if the vector is close to zero in all dimensions.
	bool NearZero()
	{
		constexpr static double epsilon = 1e-8;

		return (fabs(m_v[0]) < epsilon && fabs(m_v[1]) < epsilon && fabs(m_v[2]) < epsilon);
	}

	
};

// Type aliases for Vector 3.
using Point3 = Vector3; // 3D Point.
using Colour = Vector3; // RGB Colour triplet.


// Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	return out << v.X() << " " << v.Y() << " " << v.Z() << '\n';
}

inline Vector3 operator+(const Vector3& v, const Vector3& u)
{
	return Vector3{ v.X() + u.X(), v.Y() + u.Y(), v.Z() + u.Z() };
}

inline Vector3 operator-(const Vector3& v, const Vector3& u)
{
	return Vector3{ v.X() - u.X(), v.Y() - u.Y(), v.Z() - u.Z() };
}

inline Vector3 operator*(const Vector3& v, const Vector3& u)
{
	return Vector3{ v.X() * u.X(), v.Y() * u.Y(), v.Z() * u.Z() };
}

inline Vector3 operator*(const Vector3& v, double t)
{
	return Vector3{ v.X() * t, v.Y() * t, v.Z() * t };
}

inline Vector3 operator*(double t, const Vector3& v)
{
	return v * t;
}

inline Vector3 operator/(const Vector3& v, double t)
{
	return v * (1 / t);
}

inline double DotProduct(const Vector3& v, const Vector3& u)
{
	return v.X() * u.X()
		 + v.Y() * u.Y()
		 + v.Z() * u.Z();
}

inline Vector3 CrossProduct(const Vector3& v, const Vector3& u)
{
	return Vector3{ v.Y() * u.Z() - v.Z() * u.Y(), 
					v.Z() * u.X() - v.X() * u.Z(), 
					v.X() * u.Y() - v.Y() * u.X() };
}

inline Vector3 UnitVector(const Vector3& v)
{
	return v / v.Magnitude();
}

inline Vector3 RandomVector3()
{
	return Vector3{ RandomDouble(), RandomDouble(), RandomDouble() };
}

inline Vector3 RandomVector3(double min, double max)
{
	return Vector3{ RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max) };
}

inline Vector3 RandomVector3InUnitSphere()
{
	while (true)
	{
		Vector3 p{ RandomVector3(-1, 1) };
		if (p.MagnitudeSquared() >= 1) continue;
		return p;
	}
}

inline Vector3 RandomUnitVector3()
{
	return UnitVector(RandomVector3InUnitSphere());
}

inline Vector3 RandomVector3InUnitDisk()
{
	while (true)
	{
		Vector3 p = Vector3{ RandomDouble(-1, 1), RandomDouble(-1, 1), 0 };
		if (p.MagnitudeSquared() >= 1) continue;
		return p;
	}
}

inline Vector3 ReflectVector(const Vector3& v, const Vector3& n)
{
	return v - 2 * (DotProduct(v, n) * n);
}

inline Vector3 RefractVector(const Vector3& incidentRay, const Vector3& normal, double etaOverEtaPrime)
{
	auto cosTheta = fmin(DotProduct(-incidentRay, normal), 1.0);

	Vector3 rayOutPerpendicular = etaOverEtaPrime * (incidentRay + cosTheta * normal);
	Vector3 rayOutParallel = -sqrt(fabs(1.0 - rayOutPerpendicular.MagnitudeSquared())) * normal;

	return rayOutPerpendicular + rayOutParallel;
}


#endif
