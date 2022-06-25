#ifndef MATERIAL_H
#define MATERIAL_H

#include <Renderer/Hittable.h>

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered) const = 0;


};

#endif
