#ifndef METAL_H
#define METAL_H

#include <Renderer/Hittable.h>
#include <Materials/Material.h>

class Metal : public Material
{
public:
	Metal(const Colour& reflectance, double fuzz)
		: m_reflectance{ reflectance }, m_fuzz{ fuzz < 1 ? fuzz : 1 }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered) const override
	{
		Vector3 reflectDirection = ReflectVector(UnitVector(rayIn.Direction()), record.Normal);

		scattered = Ray{ record.Point, reflectDirection + m_fuzz * RandomVector3InUnitSphere() };
		attenuation = m_reflectance;

		return DotProduct(record.Normal, reflectDirection) > 0;
	}


private:
	Colour m_reflectance;
	double m_fuzz;
};

#endif