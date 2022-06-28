#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include <Renderer/Hittable.h>
#include <Materials/Material.h>
#include <Textures/Texture.h>

class DiffuseLight : public Material
{
public:
	DiffuseLight(shared_ptr<Texture> emitTexture)
		: m_emit{ emitTexture }
	{

	}

	DiffuseLight(const Colour& emitColour)
		: m_emit{ make_shared <SolidColour>(emitColour) }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered) const override
	{
		return false;
	}

	virtual Colour Emitted(double u, double v, Point3& p) const override
	{
		return m_emit->Value(u, v, p);
	}


private:
	shared_ptr<Texture>	m_emit;

};

#endif