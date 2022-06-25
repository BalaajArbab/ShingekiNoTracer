#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H


#include <Renderer/Hittable.h>
#include <Materials/Material.h>


class Lambertian : public Material
{
public:
	Lambertian(const Colour& reflectance)
		: m_reflectance{ reflectance }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered) const override
	{
		Vector3 scatterDirection = record.Normal + RandomUnitVector3();

		// Catch degenerate scatter direction (random unit vector is opposite the normal hence results in a zero direction vector)((which is bad))
		if (scatterDirection.NearZero()) scatterDirection = record.Normal;

		scattered = Ray{ record.Point, scatterDirection };
		attenuation = m_reflectance;

		return true;
	}


private:
	Colour m_reflectance;

};

#endif