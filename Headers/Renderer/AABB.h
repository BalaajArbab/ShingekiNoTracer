#ifndef AABB_H
#define AABB_H

#include <Math/Vector3.h>
#include <Renderer/Ray.h>
#include <Renderer/Hittable.h>

class AABB
{
public:
	AABB() = default;

	AABB(const Point3& min, const Point3& max)
		: m_minPoint{ min }, m_maxPoint{ max }
	{

	}

	Point3 Min() const { return m_minPoint; };
	Point3 Max() const { return m_maxPoint; };

	bool Hit(const Ray& r, double tMin, double tMax) const;

	friend std::ostream& operator<<(std::ostream& out, const AABB& aabb);

private:
	Point3 m_minPoint;
	Point3 m_maxPoint;

};

inline std::ostream& operator<<(std::ostream& out, const AABB& aabb)
{
	out << "Box Points:\n" << aabb.m_minPoint << aabb.m_maxPoint;

	return out;
}

//inline bool AABB::Hit(const Ray& r, double tMin, double tMax) const
//{
//	for (int i = 0; i < 3; ++i)
//	{
//		double t0 = fmin((m_minPoint[i] - r.Origin()[i]) / r.Direction()[i],
//						 (m_maxPoint[i] - r.Origin()[i]) / r.Direction()[i]);
//		double t1 = fmax((m_minPoint[i] - r.Origin()[i]) / r.Direction()[i],
//						 (m_maxPoint[i] - r.Origin()[i]) / r.Direction()[i]);
//
//		tMin = fmax(t0, tMin);
//		tMax = fmin(t1, tMax);
//
//		if (tMin >= tMax) return false;
//	}
//
//	return true;
//}

inline bool AABB::Hit(const Ray& r, double tMin, double tMax) const
{
	/*if (m_minPoint.X() < r.Origin().X() && r.Origin().X() < m_maxPoint.X()
		&& m_minPoint.Y() < r.Origin().Y() && r.Origin().Y() < m_maxPoint.Y()
		&& m_minPoint.Z() < r.Origin().Z() && r.Origin().Z() < m_maxPoint.Z())
		return true;*/

	for (int i = 0; i < 3; ++i)
	{
		double inverseDirection = 1.0 / r.Direction()[i];

		double t0 = (m_minPoint[i] - r.Origin()[i]) * inverseDirection;
		double t1 = (m_maxPoint[i] - r.Origin()[i]) * inverseDirection;

		if (inverseDirection < 0.0) std::swap(t0, t1);

		tMin = (t0 > tMin ? t0 : tMin);
		tMax = (t1 < tMax ? t1 : tMax);

		if (tMin >= tMax) return false;
	}

	return true;
}

inline AABB SurroundingBox(const AABB& box1, const AABB& box2)
{
	Point3 less{ fmin(box1.Min()[0], box2.Min()[0]),
				  fmin(box1.Min()[1], box2.Min()[1]),
				  fmin(box1.Min()[2], box2.Min()[2]) };

	Point3 more{ fmax(box1.Max()[0], box2.Max()[0]),
				  fmax(box1.Max()[1], box2.Max()[1]),
				  fmax(box1.Max()[2], box2.Max()[2]) };

	//std::cout << box1 << "combined with\n" << box2 << "to form\n" << AABB{ less, more };

	return AABB{ less, more };
}

inline bool BoxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, std::int32_t axis)
{
	AABB boxA;
	AABB boxB;

	if (!(a->BoundingBox(boxA)) || !(b->BoundingBox(boxB))) std::cerr << "Error: No bounding box";

	return boxA.Min()[axis] < boxB.Min()[axis];
}

inline bool xBoxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b)
{
	return BoxCompare(a, b, 0);
}

inline bool yBoxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b)
{
	return BoxCompare(a, b, 1);
}

inline bool zBoxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b)
{
	return BoxCompare(a, b, 2);
}

#endif