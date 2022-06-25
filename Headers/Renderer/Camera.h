#ifndef CAMERA_H
#define CAMERA_H

#include <Utility/Utility.h>

class Camera
{
public:
	Camera(Point3 lookFrom, Point3 lookAt, Vector3 vup = Vector3{ 0, 1, 0 }, double vFOV = 90, double aspectRatio = 16.0 / 9.0, double aperture = 0.01, double focusDistance = 1.0, double rotateAngle = 0)
	{
		const double theta{ DegreesToRadians(vFOV) };
		const double h{ tan(theta / 2.0) };
		const double viewportHeight{ 2.0 * h };
		const double viewportLength{ viewportHeight * aspectRatio };

		lookFrom = RotateAboutY(lookFrom, rotateAngle);

		m_w = UnitVector(lookFrom - lookAt);
		m_u = UnitVector(CrossProduct(vup, m_w));
		m_v = CrossProduct(m_w, m_u);

		std::cout << "LookFrom: " << lookFrom << "LookAt: " << lookAt << "w: " << m_w;

		m_origin = lookFrom;
		m_vertical = focusDistance * viewportHeight * m_v;
		m_horizontal = focusDistance * viewportLength * m_u;
		m_lowerLeftCorner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - focusDistance * m_w;

		m_lensRadius = aperture / 2.0;
	}

	Ray getRay(const double s, const double t) const
	{
		Vector3 rd = m_lensRadius * RandomVector3InUnitDisk();
		Vector3 offset = rd.X() * m_u + rd.Y() * m_v;

		return Ray{ m_origin + offset, (m_lowerLeftCorner + m_horizontal*s + m_vertical*t) - (m_origin + offset) };
	}

	static Point3 RotateAboutY(Point3 origin, double angle)
	{
		const double theta = DegreesToRadians(angle);

		double newX = origin.X() * cos(theta) + origin.Z() * sin(theta);
		double newZ = origin.X() * -sin(theta) + origin.Z() * cos(theta);

		Point3 newLookFrom{ newX, origin.Y(), newZ };
		return newLookFrom;
	}

private:
	Point3 m_origin;
	Point3 m_lowerLeftCorner;
	Vector3 m_vertical;
	Vector3 m_horizontal;
	Vector3 m_w;
	Vector3 m_u;
	Vector3 m_v;
	double m_lensRadius;

};

#endif