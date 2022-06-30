#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <Renderer/Hittable.h>
#include <Materials/Material.h>

class Dielectric : public Material
{
public:
	Dielectric(double indexOfRefraction)
		: m_iR{ indexOfRefraction }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered, int id) const override
	{
		attenuation = Colour{ 1.0, 1.0, 1.0 };
		double refractionRatio = record.FrontFace ? (1.0 / m_iR) : m_iR;

		Vector3 unitDirection = UnitVector(rayIn.Direction());
		double cosTheta = fmin(DotProduct(-unitDirection, record.Normal), 1.0);
		double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0;

		Vector3 direction;

		if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble(id))
		{
			direction = ReflectVector(unitDirection, record.Normal);
		}
		else direction = RefractVector(unitDirection, record.Normal, refractionRatio);

		scattered = Ray{ record.Point, direction };

		return true;
	}


private:
	double m_iR; // Index of Refraction.

	static double Reflectance(double cosine, double refIDX)
	{
		// Schlick's Approximation
		auto r0 = (1 - refIDX) / (1 + refIDX);
		r0 = r0 * r0;

		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

};

#endif