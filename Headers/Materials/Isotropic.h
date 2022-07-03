#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include <Materials/Material.h>
#include <Textures/Texture.h>

class Isotropic : public Material
{
public:
	Isotropic(const Colour& colour)
		: m_reflectance{ make_shared<SolidColour>(colour) }
	{

	}

	Isotropic(shared_ptr<Texture> texture)
		: m_reflectance{ texture }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered, int id) const override
	{
		scattered = Ray{ record.Point, RandomVector3InUnitSphere(id) };
		attenuation = m_reflectance->Value(record.u, record.v, record.Point);

		return true;
	}

private:
	shared_ptr<Texture> m_reflectance;

};

#endif