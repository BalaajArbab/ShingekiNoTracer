#ifndef BOX_H
#define BOX_H

#include <Utility/Utility.h>
#include <Shapes/AARects.h>
#include <Renderer/HittableList.h>

class Box : public Hittable
{
public:
	Box() = default;

	Box(const Point3& boxMin, const Point3& boxMax, shared_ptr<Material> material);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;
	virtual bool BoundingBox(AABB& outBox) const override
	{
		outBox = AABB{ m_boxMin, m_boxMax };

		return true;
	}

private:
	Point3 m_boxMin;
	Point3 m_boxMax;
	HittableList m_sides;

};

inline Box::Box(const Point3& boxMin, const Point3& boxMax, shared_ptr<Material> material)
	: m_boxMin{ boxMin }, m_boxMax{ boxMax }
{
	m_sides.Add(make_shared<XYRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Y(), m_boxMax.Y(), m_boxMin.Z(), material));
	m_sides.Add(make_shared<XYRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Y(), m_boxMax.Y(), m_boxMax.Z(), material));

	m_sides.Add(make_shared<XZRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Z(), m_boxMax.Z(), m_boxMin.Y(), material));
	m_sides.Add(make_shared<XZRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Z(), m_boxMax.Z(), m_boxMax.Y(), material));

	m_sides.Add(make_shared<YZRect>(m_boxMin.Y(), m_boxMax.Y(), m_boxMin.Z(), m_boxMax.Z(), m_boxMin.X(), material));
	m_sides.Add(make_shared<YZRect>(m_boxMin.Y(), m_boxMax.Y(), m_boxMin.Z(), m_boxMax.Z(), m_boxMax.X(), material));
}

inline bool Box::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	return m_sides.Hit(r, tMin, tMax, record);
}

#endif