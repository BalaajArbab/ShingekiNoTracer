#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H


#include <Renderer/Hittable.h>
#include <Materials/Material.h>
#include <Textures/Texture.h>


class Lambertian : public Material
{
public:
	Lambertian(const Colour& reflectanceTexture)
		: m_reflectanceTexture{ make_shared<SolidColour>(reflectanceTexture) }
	{

	}

	Lambertian(shared_ptr<Texture> reflectanceTexture)
		: m_reflectanceTexture{ reflectanceTexture }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered, int id) const override
	{
		Vector3 scatterDirection = record.Normal + RandomUnitVector3(id);

		// Catch degenerate scatter direction (random unit vector is opposite the normal hence results in a zero direction vector)((which is bad))
		if (scatterDirection.NearZero()) scatterDirection = record.Normal;

		scattered = Ray{ record.Point, scatterDirection };
		attenuation = m_reflectanceTexture->Value(record.u, record.v, record.Point);

		return true;
	}


private:
	shared_ptr<Texture> m_reflectanceTexture;

};

#endif