#ifndef HITTABLE_H
#define HITTABLE_H

#include <Math/Vector3.h>
#include <Renderer/Ray.h>

class Material;

struct HitRecord
{
	Point3 Point;
	Vector3 Normal;
	double t;
	bool FrontFace;
	shared_ptr<Material> Material_ptr;

	void SetFaceNormal(const Ray& r, const Vector3& outwardNormal)
	{
		FrontFace = DotProduct(r.Direction(), outwardNormal) < 0;
		Normal = FrontFace ? outwardNormal : -outwardNormal;
	}

};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const = 0;

};

#endif