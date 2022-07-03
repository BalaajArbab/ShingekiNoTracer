#ifndef HITTABLE_H
#define HITTABLE_H

#include <Math/Vector3.h>
#include <Renderer/Ray.h>

class AABB;
class Material;

struct HitRecord
{
	Point3 Point;
	Vector3 Normal;
	double t;
	bool FrontFace;
	shared_ptr<Material> Material_ptr;

	double u;
	double v;

	void SetFaceNormal(const Ray& r, const Vector3& outwardNormal)
	{
		FrontFace = DotProduct(r.Direction(), outwardNormal) < 0;
		Normal = FrontFace ? outwardNormal : -outwardNormal;
	}

};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const = 0;
	virtual bool BoundingBox(AABB& outBox) const = 0;
};

#endif