#ifndef BOX_H
#define BOX_H

#include <Utility/Utility.h>
#include <Shapes/AARects.h>
#include <Renderer/HittableList.h>
#include <bitset>
#include <Materials/Metal.h>

class Box : public Hittable
{
public:
	Box() = default;

	Box(const Point3& boxMin, const Point3& boxMax, shared_ptr<Material> material, std::bitset<6> mirrorMask, shared_ptr<Material> otherMat);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const override;
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

inline Box::Box(const Point3& boxMin, const Point3& boxMax, shared_ptr<Material> material, std::bitset<6> mirrorMask = std::bitset<6>{ 0b000000 }, shared_ptr<Material> otherMat = make_shared<Metal>(Colour{1, 1, 1}, 0.0))
	: m_boxMin{ boxMin }, m_boxMax{ boxMax }
{
	auto backWall = make_shared<XYRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Y(), m_boxMax.Y(), m_boxMin.Z(), material);
	auto frontWall = make_shared<XYRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Y(), m_boxMax.Y(), m_boxMax.Z(), material);

	auto bottomWall = make_shared<XZRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Z(), m_boxMax.Z(), m_boxMin.Y(), material);
	auto topWall = make_shared<XZRect>(m_boxMin.X(), m_boxMax.X(), m_boxMin.Z(), m_boxMax.Z(), m_boxMax.Y(), material);

	auto leftWall = make_shared<YZRect>(m_boxMin.Y(), m_boxMax.Y(), m_boxMin.Z(), m_boxMax.Z(), m_boxMin.X(), material);
	auto rightWall = make_shared<YZRect>(m_boxMin.Y(), m_boxMax.Y(), m_boxMin.Z(), m_boxMax.Z(), m_boxMax.X(), material);

	if (mirrorMask.test(0)) backWall->SetMaterial(otherMat);
	if (mirrorMask.test(1)) frontWall->SetMaterial(otherMat);
	if (mirrorMask.test(2)) bottomWall->SetMaterial(otherMat);
	if (mirrorMask.test(3)) topWall->SetMaterial(otherMat);
	if (mirrorMask.test(4)) leftWall->SetMaterial(otherMat);
	if (mirrorMask.test(5)) rightWall->SetMaterial(otherMat);

	m_sides.Add(backWall);
	m_sides.Add(frontWall);
	m_sides.Add(bottomWall);
	m_sides.Add(topWall);
	m_sides.Add(leftWall);
	m_sides.Add(rightWall);
}

inline bool Box::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const
{
	return m_sides.Hit(r, tMin, tMax, record, id);
}

#endif