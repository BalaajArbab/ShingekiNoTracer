#ifndef SPHERE_H
#define SPHERE_H

#include <Math/Vector3.h>
#include <Renderer/Hittable.h>

class Sphere : public Hittable
{
private:
	Point3 m_center;
	double m_radius;
	shared_ptr<Material> m_materialPtr;

public:
	Sphere() = default;

	Sphere(Point3 c, double r, shared_ptr<Material> m)
		: m_center{ c }, m_radius{ r }, m_materialPtr{ m }
	{}

	Sphere(Point3 c, double r)
		: m_center{ c }, m_radius{ r }
	{}

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

};

inline bool Sphere::Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
	Vector3 oc = r.Origin() - m_center;

	auto a = r.Direction().MagnitudeSquared();
	auto halfB = DotProduct(oc, r.Direction());
	auto c = oc.MagnitudeSquared() - m_radius * m_radius;

	auto discriminant = halfB * halfB - a * c;
	if (discriminant < 0) return false;
	
	auto sqrtD = sqrt(discriminant);

	// Find nearest root(smallest t value) that lies within the acceptable range.
	auto root = (-halfB - sqrtD) / a;

	if (root < tMin || root > tMax)
	{
		root = (-halfB + sqrtD) / a;

		if (root < tMin || root > tMax) return false;
	}

	record.t = root;
	record.Point = r.At(root);
	record.Material_ptr = m_materialPtr;

	auto outwardNormal = (record.Point - m_center) / m_radius;
	record.SetFaceNormal(r, outwardNormal);


	return true;
}

#endif