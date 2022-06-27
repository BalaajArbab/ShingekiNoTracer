#ifndef TEXTURE_H
#define TEXTURE_H

#include <Utility/Utility.h>
#include <Math/Vector3.h>

class Texture
{
public:
	virtual Colour Value(double u, double v, const Point3& p) const = 0;

};

class SolidColour : public Texture
{
public:
	SolidColour() = default;

	SolidColour(const Colour& c)
		: m_colourValue{ c }
	{

	}

	SolidColour(double r, double g, double b)
		: SolidColour{ Colour{ r, g, b } }
	{

	}

	virtual Colour Value(double u, double v, const Point3& p) const override
	{
		return m_colourValue;
	}

private:
	Colour m_colourValue;

};



#endif