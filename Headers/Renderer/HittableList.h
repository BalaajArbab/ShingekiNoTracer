#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <Renderer/Hittable.h>
#include <Renderer/AABB.h>

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
	HittableList() = default;

	HittableList(shared_ptr<Hittable> object)
	{
		Add(object);
	}

	void Add(shared_ptr<Hittable> object)
	{
		m_objects.push_back(object);
	}

	void Clear()
	{
		m_objects.resize(0);
	}

	const std::vector<shared_ptr<Hittable>>& GetList() const
	{
		return m_objects;
	}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id, int depth) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

private:
	std::vector<shared_ptr<Hittable>> m_objects;

};

inline bool HittableList::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id, int depth) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	auto closestSoFar = tMax;

	for (const auto& object : m_objects)
	{
		if (object->Hit(r, tMin, tMax, tempRecord, id, depth))
		{
			hitAnything = true;

			if (tempRecord.t < closestSoFar)
			{
				closestSoFar = tempRecord.t;
				record = tempRecord;
			}

		}
	}

	return hitAnything;
}

inline bool HittableList::BoundingBox(AABB& outBox) const
{
	if (m_objects.empty()) return false;

	AABB tempBox;
	bool firstBox = true;

	for (auto object : m_objects)
	{
		if (!object->BoundingBox(tempBox)) return false;

		outBox = firstBox ? tempBox : SurroundingBox(outBox, tempBox);
		firstBox = false;
	}

	return true;
}

#endif