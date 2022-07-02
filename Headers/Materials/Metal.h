#ifndef METAL_H
#define METAL_H

#include <Renderer/Hittable.h>
#include <Materials/Material.h>
#include <Textures/Texture.h>

class Metal : public Material
{
public:
	Metal(const Colour& reflectance, double fuzz)
		: m_reflectance{ make_shared<SolidColour>(reflectance) }, m_fuzz{fuzz < 1 ? fuzz : 1}
	{

	}

	Metal(shared_ptr<Texture> reflectance, double fuzz)
		: m_reflectance{ reflectance }, m_fuzz{ fuzz < 1 ? fuzz : 1 }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered, int id) const override
	{
		Vector3 reflectDirection = ReflectVector(UnitVector(rayIn.Direction()), record.Normal);

		scattered = Ray{ record.Point, reflectDirection + m_fuzz * RandomVector3InUnitSphere(id) };
		attenuation = m_reflectance->Value(record.u, record.v, record.Point);

		return DotProduct(record.Normal, reflectDirection) > 0;
	}


private:
	shared_ptr<Texture> m_reflectance;
	double m_fuzz;
};

#endif
