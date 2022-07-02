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
	virtual bool BoundingBox(AABB& outBox) const override;

	static void GetSphereUV(const Point3& p, double& u, double& v);

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

	GetSphereUV(outwardNormal, record.u, record.v);

	return true;
}

inline bool Sphere::BoundingBox(AABB& outBox) const
{
	outBox = AABB{ m_center - Vector3{ m_radius, m_radius, m_radius }, m_center + Vector3{ m_radius, m_radius, m_radius } };

	return true;
}

inline void Sphere::GetSphereUV(const Point3& p, double& u, double& v)
{
	// p: a given point on the sphere of radius one, centered at the origin.
			// u: returned value [0,1] of angle around the Y axis from X=-1.
			// v: returned value [0,1] of angle from Y=-1 to Y=+1.
			//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
			//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
			//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

	auto p1 = UnitVector(p);

	auto theta = acos(-p1.Y());
	auto phi = atan2(-p1.Z(), p1.X()) + pi;

	u = phi / (pi * 2);
	v = theta / pi;
}

#endif
