#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <Renderer/HittableList.h>

class Translate : public Hittable
{
public:
	Translate(shared_ptr<Hittable> object, const Vector3& displacement)
		: m_object{ object }, m_offset{ displacement }
	{

	}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id, int depth) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

private:
	shared_ptr<Hittable> m_object;
	Vector3 m_offset;

};

inline bool Translate::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id, int depth) const
{
	Ray movedRay{ r.Origin() - m_offset, r.Direction()};

	if (!m_object->Hit(movedRay, tMin, tMax, record, id, depth)) return false;

	record.Point += m_offset;
	record.SetFaceNormal(movedRay, record.Normal);

	return true;
}

inline bool Translate::BoundingBox(AABB& outBox) const
{
	if (!m_object->BoundingBox(outBox)) return false;

	outBox = AABB(outBox.Min() + m_offset, outBox.Max() + m_offset);

	return true;
}

#endif