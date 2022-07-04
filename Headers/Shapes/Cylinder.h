#ifndef CYLINDER_H
#define CYLINDER_H

#include <Math/Vector3.h>
#include <Renderer/Hittable.h>

inline bool outOfBoundsZ(double zPoint, double z0, double z1);

class Cylinder : public Hittable
{
public:
	Cylinder(double z0, double z1, double r, shared_ptr<Material> m)
		: m_z0{ z0 }, m_z1{ z1 }, m_radius{ r }, m_materialPtr{ m }
	{}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id, int depth) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

	static void GetCylinderUV(const Point3& p, double& u, double& v);

public:
	Point3 m_center{ 0, 0, 0 };
	double m_z0;
	double m_z1;
	double m_radius;
	shared_ptr<Material> m_materialPtr;

};

inline bool Cylinder::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id, int depth) const
{
	double xOri = r.Origin().X();
	double yOri = r.Origin().Y();

	double xDir = r.Direction().X();
	double yDir = r.Direction().Y();

	bool capHit = false;
	HitRecord capRecord;

	XYRect topCap{ 0 - m_radius, 0 + m_radius, 0 - m_radius, 0 + m_radius, m_z1, m_materialPtr };

	if (topCap.Hit(r, tMin, tMax, record, id, depth))
	{
		auto toCenter = record.Point - m_center - Vector3{ 0, 0, record.Point.Z() };

		if (toCenter.Magnitude() < m_radius)
		{
			capHit = true;
		}
	}

	XYRect bottomCap{ 0 - m_radius, 0 + m_radius, 0 - m_radius, 0 + m_radius, m_z0, m_materialPtr };

	if (bottomCap.Hit(r, tMin, (capHit ? record.t : tMax), record, id, depth))
	{
		auto toCenter = record.Point - m_center - Vector3{ 0, 0, record.Point.Z() };

		if (toCenter.Magnitude() < m_radius) capHit = true;
	}

	if (capHit)
	{
		tMax = record.t;
		capRecord = record;
	}


	double a = xDir * xDir + yDir * yDir;
	double halfB = xOri * xDir + yOri * yDir;
	double c = xOri * xOri + yOri * yOri - m_radius * m_radius;

	auto discriminant = halfB * halfB - a * c;

	if (discriminant < 0 && capHit) return true;
	if (discriminant < 0) return false;
	

	auto sqrtD = sqrt(discriminant);

	// Find nearest root(smallest t value) that lies within the acceptable range.
	auto root = (-halfB - sqrtD) / a;

	record.t = root;
	record.Point = r.At(root);

	if (root < tMin || root > tMax || outOfBoundsZ(record.Point.Z(), m_z0, m_z1))
	{
		root = (-halfB + sqrtD) / a;
		record.t = root;
		record.Point = r.At(root);

		if ((root < tMin || root > tMax || outOfBoundsZ(record.Point.Z(), m_z0, m_z1)) && !capHit)
		{
			return false;
		}
		else if (capHit)
		{
			record = capRecord;
			return true;
		}
	}

	record.Material_ptr = m_materialPtr;

	auto outwardNormal = (record.Point - m_center - Vector3{ 0, 0, record.Point.Z() }) / m_radius;
	record.SetFaceNormal(r, outwardNormal);

	return true;
}

inline bool Cylinder::BoundingBox(AABB& outBox) const
{
	Point3 min{ m_center - Vector3{ m_radius, m_radius, 0 } + Vector3{ 0, 0, m_z0 - 0.001 } };
	Point3 max{ m_center + Vector3{ m_radius, m_radius, m_z1 + 0.001 } };

	outBox = AABB{ min, max };

	return true;
}

inline void Cylinder::GetCylinderUV(const Point3& p, double& u, double& v)
{

}

inline bool outOfBoundsZ(double zPoint, double z0, double z1)
{
	return (zPoint < z0 || zPoint > z1);
}

#endif