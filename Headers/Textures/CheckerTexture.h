#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include <Textures/Texture.h>

class CheckerTexture : public Texture
{
public:
	CheckerTexture() = default;

	CheckerTexture(shared_ptr<Texture> even, shared_ptr<Texture> odd)
		: m_even{ even }, m_odd{ odd }
	{

	}

	CheckerTexture(const Colour& c1, const Colour& c2)
		: m_even{ make_shared<SolidColour>(c1) }, m_odd{ make_shared<SolidColour>(c2) }
	{

	}

	virtual Colour Value(double u, double v, const Point3& p) const override
	{
		auto sines = sin(m_frequency * p.X()) * sin(m_frequency * p.Y()) * sin(m_frequency * p.Z());

		if (sines < 0) return m_odd->Value(u, v, p);

		return m_even->Value(u, v, p);
	}

	void SetFrequency(double freq)
	{
		m_frequency = freq;
	}

private:
	shared_ptr<Texture> m_even;
	shared_ptr<Texture> m_odd;
	double m_frequency{ 1 };

};

#endif
