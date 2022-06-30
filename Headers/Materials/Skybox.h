#ifndef Skybox_H
#define Skybox_H


#include <Renderer/Hittable.h>
#include <Materials/Material.h>
#include <Textures/Texture.h>


class Skybox : public Material
{
public:
	Skybox(const Colour& reflectanceTexture)
		: m_reflectanceTexture{ make_shared<SolidColour>(reflectanceTexture) }
	{

	}

	Skybox(shared_ptr<Texture> reflectanceTexture)
		: m_reflectanceTexture{ reflectanceTexture }
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Colour& attenuation, Ray& scattered, int id) const override
	{
		return false;
	}

	virtual Colour Emitted(double u, double v, Point3& p) const override
	{
		return m_reflectanceTexture->Value(u, v, p);
	}


private:
	shared_ptr<Texture> m_reflectanceTexture;

};

#endif