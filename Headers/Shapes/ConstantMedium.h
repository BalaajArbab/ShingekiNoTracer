#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include <Utility/Utility.h>
#include <Renderer/Hittable.h>
#include <Materials/Material.h>
#include <Materials/Isotropic.h>
#include <Textures/Texture.h>


class ConstantMedium : public Hittable
{
public:
	ConstantMedium(shared_ptr<Hittable> boundary, double density, shared_ptr<Texture> texture)
		: m_boundary{ boundary }, m_negInvDensity{ -1 / density }, m_phaseFunction{ make_shared<Isotropic>(texture)}
	{

	}

	ConstantMedium(shared_ptr<Hittable> boundary, double density, const Colour& colour)
		: m_boundary{ boundary }, m_negInvDensity{ -1 / density }, m_phaseFunction{ make_shared<Isotropic>(colour)}
	{

	}


	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const override;
	virtual bool BoundingBox(AABB& outBox) const override;

private:
	shared_ptr<Hittable> m_boundary;
	shared_ptr<Material> m_phaseFunction;
	double m_negInvDensity;

};

inline bool ConstantMedium::Hit(const Ray& r, double tMin, double tMax, HitRecord& record, int id) const
{
	// Print occasional samples when debugging. To enable, set enableDebug true.
	const bool enableDebug = false;
	const bool debugging = enableDebug && RandomDouble(id) < 0.00001;

	HitRecord record1;
	HitRecord record2;

	if (!m_boundary->Hit(r, -infinity, infinity, record1, id)) return false;

	if (!m_boundary->Hit(r, record1.t + 0.0001, infinity, record2, id)) return false;

	if (debugging) std::cout << "tMin: " << record1.t << ", tMax: " << record2.t << '\n';

	if (record1.t < tMin) record1.t = tMin;
	if (record2.t > tMax) record2.t = tMax;

	if (record1.t >= record2.t) return false;

	if (record1.t < 0) record1.t = 0;

	const double rayLength = r.Direction().Magnitude();
	const double distanceInsideBoundary = (record2.t - record1.t) * rayLength;
	const double hitDistance = m_negInvDensity * log(RandomDouble(id));

	if (hitDistance > distanceInsideBoundary) return false;

	record.t = record1.t + hitDistance / rayLength;
	record.Point = r.At(record.t);

	if (debugging) std::cout << "hitDistance: " << hitDistance << " record.t: " << record.t << " record.Point: " << record.Point << '\n';

	record.Normal = Vector3{ 1, 0, 0 }; // Arbitrary.
	record.FrontFace = true; // Also arbitrary.
	record.Material_ptr = m_phaseFunction;

	return true;
}

inline bool ConstantMedium::BoundingBox(AABB& outBox) const
{
	return m_boundary->BoundingBox(outBox);
}

#endif