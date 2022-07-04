#ifndef AARECTS_H
#define AARECTS_H

#include <Utility/Utility.h>
#include <Renderer/Hittable.h>

class XYRect : public Hittable
{
public:
	XYRect() = default;

	XYRect(double x0, double x1, double y0, double y1, double z, shared_ptr<Material> mat)
		: m_x0{ x0 }, m_x1{ x1 }, m_y0{ y0 }, m_y1{ y1 }, m_z{ z }, m_materialPtr{ mat }
	{

	}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

	void SetMaterial(shared_ptr<Material> newMat)
	{
		m_materialPtr = newMat;
	}

	void MakeInvisible()
	{
		m_invisible = true;
	}

private:
	shared_ptr<Material> m_materialPtr;
	double m_x0;
	double m_x1;
	double m_y0;
	double m_y1;
	double m_z;
	bool m_invisible{ false };

};

inline bool XYRect::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const
{
	double t = (m_z - r.Origin().Z()) / r.Direction().Z();

	if (t < tMin || t > tMax) return false;

	double x = r.Origin().X() + r.Direction().X() * t;
	double y = r.Origin().Y() + r.Direction().Y() * t;

	if (x < m_x0 || x > m_x1 || y < m_y0 || y > m_y1) return false;

	record.u = (x - m_x0) / (m_x1 - m_x0);
	record.v = (y - m_y0) / (m_y1 - m_y0);

	record.t = t;

	Vector3 outwardNormal = Vector3{ 0, 0, 1 };
	record.SetFaceNormal(r, outwardNormal);

	record.Material_ptr = m_materialPtr;
	record.Point = r.At(t);
	
	return true;
}

inline bool XYRect::BoundingBox(AABB& outBox) const
{
	outBox = AABB{ Point3{ m_x0, m_y0, m_z - 0.0001 }, Point3{ m_x1, m_y1, m_z + 0.0001 } };

	return true;
}


class XZRect : public Hittable
{
public:
	XZRect() = default;

	XZRect(double x0, double x1, double z0, double z1, double y, shared_ptr<Material> mat)
		: m_x0{ x0 }, m_x1{ x1 }, m_z0{ z0 }, m_z1{ z1 }, m_y{ y }, m_materialPtr{ mat }
	{

	}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

	void SetMaterial(shared_ptr<Material> newMat)
	{
		m_materialPtr = newMat;
	}

private:
	shared_ptr<Material> m_materialPtr;
	double m_x0;
	double m_x1;
	double m_z0;
	double m_z1;
	double m_y;

};

inline bool XZRect::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const
{
	double t = (m_y - r.Origin().Y()) / r.Direction().Y();

	if (t < tMin || t > tMax) return false;

	double x = r.Origin().X() + r.Direction().X() * t;
	double z = r.Origin().Z() + r.Direction().Z() * t;

	if (x < m_x0 || x > m_x1 || z < m_z0 || z > m_z1) return false;

	record.u = (x - m_x0) / (m_x1 - m_x0);
	record.v = (z - m_z0) / (m_z1 - m_z0);

	record.t = t;

	Vector3 outwardNormal = Vector3{ 0, 1, 0 };
	record.SetFaceNormal(r, outwardNormal);

	record.Material_ptr = m_materialPtr;
	record.Point = r.At(t);

	return true;
}

inline bool XZRect::BoundingBox(AABB& outBox) const
{
	outBox = AABB{ Point3{ m_x0, m_y - 0.0001, m_z0 }, Point3{ m_x1, m_y + 0.0001, m_z1 } };

	return true;
}

class YZRect : public Hittable
{
public:
	YZRect() = default;

	YZRect(double y0, double y1, double z0, double z1, double x, shared_ptr<Material> mat)
		: m_y0{ y0 }, m_y1{ y1 }, m_z0{ z0 }, m_z1{ z1 }, m_x{ x }, m_materialPtr{ mat }
	{

	}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

	void SetMaterial(shared_ptr<Material> newMat)
	{
		m_materialPtr = newMat;
	}

private:
	shared_ptr<Material> m_materialPtr;
	double m_y0;
	double m_y1;
	double m_z0;
	double m_z1;
	double m_x;

};

inline bool YZRect::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const
{
	double t = (m_x - r.Origin().X()) / r.Direction().X();

	if (t < tMin || t > tMax) return false;

	double y = r.Origin().Y() + r.Direction().Y() * t;
	double z = r.Origin().Z() + r.Direction().Z() * t;

	if (y < m_y0 || y > m_y1 || z < m_z0 || z > m_z1) return false;

	record.u = (y - m_y0) / (m_y1 - m_y0);
	record.v = (z - m_z0) / (m_z1 - m_z0);

	record.t = t;

	Vector3 outwardNormal = Vector3{ 1, 0, 0 };
	record.SetFaceNormal(r, outwardNormal);

	record.Material_ptr = m_materialPtr;
	record.Point = r.At(t);

	return true;
}

inline bool YZRect::BoundingBox(AABB& outBox) const
{
	outBox = AABB{ Point3{ m_x - 0.0001, m_y0, m_z0,  }, Point3{ m_x + 0.0001, m_y1, m_z1 } };

	return true;
}

#endif