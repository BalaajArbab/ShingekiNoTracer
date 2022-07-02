#ifndef ROTATIONS_H
#define ROTATIONS_H

#include <cmath>
#include <Renderer/HittableList.h>

class RotateY : public Hittable
{
public:
	RotateY(shared_ptr<Hittable> object, double angle);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

	virtual bool BoundingBox(AABB& outBox) const override
	{
		outBox = m_boundingBox;

		return m_hasBox;
	}

private:
	shared_ptr<Hittable> m_object;
	double m_sinTheta;
	double m_cosTheta;
	bool m_hasBox;
	AABB m_boundingBox;

};

inline RotateY::RotateY(shared_ptr<Hittable> object, double angle)
	: m_object{ object }
{
	double radians = DegreesToRadians(angle);

	m_sinTheta = sin(radians);
	m_cosTheta = cos(radians);

	m_hasBox = m_object->BoundingBox(m_boundingBox);

	Point3 min{ infinity, infinity, infinity };
	Point3 max{ -infinity, -infinity, -infinity };

	// Iterates through the 8 points/corners of the bounding box.
	for (int i = 0; i < 2; i++) 
	{
		for (int j = 0; j < 2; j++) 
		{
			for (int k = 0; k < 2; k++) 
			{
				double x = i * m_boundingBox.Max().X() + (1 - i) * m_boundingBox.Min().X();
				double y = j * m_boundingBox.Max().Y() + (1 - j) * m_boundingBox.Min().Y();
				double z = k * m_boundingBox.Max().Z() + (1 - k) * m_boundingBox.Min().Z();

				double newX = m_cosTheta * x + m_sinTheta * z;
				double newZ = -m_sinTheta * x + m_cosTheta * z;

				Vector3 tester{ newX, y, newZ };

				for (int c = 0; c < 3; ++c)
				{
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}

			}
		}
	}

	m_boundingBox = AABB{ min, max };
}

inline bool RotateY::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	Point3 origin = r.Origin();
	Point3 direction = r.Direction();

	origin[0] = m_cosTheta * r.Origin()[0] - m_sinTheta * r.Origin()[2];
	origin[2] = m_sinTheta * r.Origin()[0] + m_cosTheta * r.Origin()[2];

	direction[0] = m_cosTheta * r.Direction()[0] - m_sinTheta * r.Direction()[2];
	direction[2] = m_sinTheta * r.Direction()[0] + m_cosTheta * r.Direction()[2];

	Ray rotatedRay{ origin, direction };

	if (!m_object->Hit(rotatedRay, tMin, tMax, record)) return false;

	Point3 point = record.Point;
	Vector3 normal = record.Normal;

	point[0] = m_cosTheta * record.Point[0] + m_sinTheta * record.Point[2];
	point[2] = -m_sinTheta * record.Point[0] + m_cosTheta * record.Point[2];

	normal[0] = m_cosTheta * record.Normal[0] + m_sinTheta * record.Normal[2];
	normal[2] = -m_sinTheta * record.Normal[0] + m_cosTheta * record.Normal[2];

	record.Point = point;
	record.SetFaceNormal(r, normal);

	return true;
}

class RotateX : public Hittable
{
public:
	RotateX(shared_ptr<Hittable> object, double angle);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

	virtual bool BoundingBox(AABB& outBox) const override
	{
		outBox = m_boundingBox;

		return m_hasBox;
	}

private:
	shared_ptr<Hittable> m_object;
	double m_sinTheta;
	double m_cosTheta;
	bool m_hasBox;
	AABB m_boundingBox;

};

inline RotateX::RotateX(shared_ptr<Hittable> object, double angle)
	: m_object{ object }
{
	double radians = DegreesToRadians(angle);

	m_sinTheta = sin(radians);
	m_cosTheta = cos(radians);

	m_hasBox = m_object->BoundingBox(m_boundingBox);

	Point3 min{ infinity, infinity, infinity };
	Point3 max{ -infinity, -infinity, -infinity };

	// Iterates through the 8 points/corners of the bounding box.
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				double x = i * m_boundingBox.Max().X() + (1 - i) * m_boundingBox.Min().X();
				double y = j * m_boundingBox.Max().Y() + (1 - j) * m_boundingBox.Min().Y();
				double z = k * m_boundingBox.Max().Z() + (1 - k) * m_boundingBox.Min().Z();

				double newY = m_cosTheta * y - m_sinTheta * z;
				double newZ = m_sinTheta * y + m_cosTheta * z;

				Vector3 tester{ x, newY, newZ };

				for (int c = 0; c < 3; c++)
				{
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}

			}
		}
	}

	m_boundingBox = AABB{ min, max };
}

inline bool RotateX::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	Point3 origin = r.Origin();
	Point3 direction = r.Direction();

	origin[1] = m_cosTheta * r.Origin()[1] + m_sinTheta * r.Origin()[2];
	origin[2] = -m_sinTheta * r.Origin()[1] + m_cosTheta * r.Origin()[2];

	direction[1] = m_cosTheta * r.Direction()[1] + m_sinTheta * r.Direction()[2];
	direction[2] = -m_sinTheta * r.Direction()[1] + m_cosTheta * r.Direction()[2];

	Ray rotatedRay{ origin, direction };

	if (!m_object->Hit(rotatedRay, tMin, tMax, record)) return false;

	Point3 point = record.Point;
	Vector3 normal = record.Normal;

	point[1] = m_cosTheta * record.Point[1] - m_sinTheta * record.Point[2];
	point[2] = m_sinTheta * record.Point[1] + m_cosTheta * record.Point[2];

	normal[1] = m_cosTheta * record.Normal[1] - m_sinTheta * record.Normal[2];
	normal[2] = m_sinTheta * record.Normal[1] + m_cosTheta * record.Normal[2];

	record.Point = point;
	record.SetFaceNormal(r, normal);


	return true;
}

class RotateZ : public Hittable
{
public:
	RotateZ(shared_ptr<Hittable> object, double angle);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

	virtual bool BoundingBox(AABB& outBox) const override
	{
		outBox = m_boundingBox;

		return m_hasBox;
	}

private:
	shared_ptr<Hittable> m_object;
	double m_sinTheta;
	double m_cosTheta;
	bool m_hasBox;
	AABB m_boundingBox;

};

inline RotateZ::RotateZ(shared_ptr<Hittable> object, double angle)
	: m_object{ object }
{
	double radians = DegreesToRadians(angle);

	m_sinTheta = sin(radians);
	m_cosTheta = cos(radians);

	m_hasBox = m_object->BoundingBox(m_boundingBox);

	Point3 min{ infinity, infinity, infinity };
	Point3 max{ -infinity, -infinity, -infinity };

	// Iterates through the 8 points/corners of the bounding box.
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				double x = i * m_boundingBox.Max().X() + (1 - i) * m_boundingBox.Min().X();
				double y = j * m_boundingBox.Max().Y() + (1 - j) * m_boundingBox.Min().Y();
				double z = k * m_boundingBox.Max().Z() + (1 - k) * m_boundingBox.Min().Z();

				double newX = m_cosTheta * x - m_sinTheta * y;
				double newY = m_sinTheta * x + m_cosTheta * y;

				Vector3 tester{ newX, newY, z };

				for (int c = 0; c < 3; c++)
				{
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}

			}
		}
	}

	m_boundingBox = AABB{ min, max };
}

inline bool RotateZ::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	Point3 origin = r.Origin();
	Point3 direction = r.Direction();

	origin[0] = m_cosTheta * r.Origin()[0] + m_sinTheta * r.Origin()[1];
	origin[1] = -m_sinTheta * r.Origin()[0] + m_cosTheta * r.Origin()[1];

	direction[0] = m_cosTheta * r.Direction()[0] + m_sinTheta * r.Direction()[1];
	direction[1] = -m_sinTheta * r.Direction()[0] + m_cosTheta * r.Direction()[1];

	Ray rotatedRay{ origin, direction };

	if (!m_object->Hit(rotatedRay, tMin, tMax, record)) return false;

	Point3 point = record.Point;
	Vector3 normal = record.Normal;

	point[0] = m_cosTheta * record.Point[0] - m_sinTheta * record.Point[1];
	point[1] = m_sinTheta * record.Point[0] + m_cosTheta * record.Point[1];

	normal[0] = m_cosTheta * record.Normal[0] - m_sinTheta * record.Normal[1];
	normal[1] = m_sinTheta * record.Normal[0] + m_cosTheta * record.Normal[1];

	record.Point = point;
	record.SetFaceNormal(r, normal);


	return true;
}

#endif