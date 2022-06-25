#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <Renderer/Hittable.h>

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

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

private:
	std::vector<shared_ptr<Hittable>> m_objects;

};

inline bool HittableList::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	auto closestSoFar = tMax;

	for (const auto& object : m_objects)
	{
		if (object->Hit(r, tMin, tMax, tempRecord))
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

#endif