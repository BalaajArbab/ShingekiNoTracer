#ifndef BVH_H
#define BVH_H

#include <Utility/Utility.h>
#include <Renderer/HittableList.h>
#include <algorithm>

class BVHNode : public Hittable
{
public:
	BVHNode() = default;

	BVHNode(const HittableList& list)
		: BVHNode(list.GetList(), 0, list.GetList().size())
	{}

	BVHNode(const std::vector<shared_ptr<Hittable>>& srcObjects, size_t start, size_t end);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

	virtual bool BoundingBox(AABB& outBox) const override;

private:
	shared_ptr<Hittable> m_leftChild;
	shared_ptr<Hittable> m_rightChild;
	AABB m_box;

};

inline BVHNode::BVHNode(const std::vector<shared_ptr<Hittable>>& srcObjects, size_t start, size_t end)
{
	auto objects = srcObjects; // Create a modifiable list of the source scene objects.

	int axis = RandomInteger(0, 2);

	auto comparator = (axis == 0) ? xBoxCompare : (axis == 1) ? yBoxCompare : zBoxCompare;

	size_t objectSpan = end - start;

	if (objectSpan == 1)
	{
		m_leftChild = objects[start];
		m_rightChild = objects[start];
	} 
	else if (objectSpan == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			m_leftChild = objects[start];
			m_rightChild = objects[start + 1];
		}
		else
		{
			m_leftChild = objects[start + 1];
			m_rightChild = objects[start];
		}
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		int mid = start + objectSpan / 2;

		m_leftChild = make_shared<BVHNode>(objects, start, mid);
		m_rightChild = make_shared<BVHNode>(objects, mid, end);
	}

	AABB boxLeft;
	AABB boxRight;

	if (!(m_leftChild->BoundingBox(boxLeft)) || !(m_rightChild->BoundingBox(boxRight))) std::cerr << "Error: No bounding box";

	m_box = SurroundingBox(boxLeft, boxRight);
}

inline bool BVHNode::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	if (!m_box.Hit(r, tMin, tMax)) return false;

	bool hitLeft = m_leftChild->Hit(r, tMin, tMax, record);
	bool hitRight = m_rightChild->Hit(r, tMin, (hitLeft ? record.t : tMax), record);

	return hitLeft || hitRight;
}

inline bool BVHNode::BoundingBox(AABB& outBox) const
{
	outBox = m_box;

	return true;
}

#endif