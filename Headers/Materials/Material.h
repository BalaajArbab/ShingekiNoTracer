#ifndef MATERIAL_H
#define MATERIAL_H

#include <Renderer/Hittable.h>

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered, int id) const = 0;

	virtual Colour Emitted(double u, double v, Point3& p) const
	{
		return Colour{ 0, 0, 0 };
	}

};

#endif
