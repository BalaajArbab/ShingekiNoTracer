#ifndef RECT_CHECKER_H
#define RECT_CHECKER_H

#include <Textures/Texture.h>

class RectChecker : public Texture
{
public:
	RectChecker(shared_ptr<Texture> even, shared_ptr<Texture> odd)
		: m_even{ even }, m_odd{ odd }
	{

	}

	RectChecker(const Colour& c1, const Colour& c2)
		: m_even{ make_shared<SolidColour>(c1) }, m_odd{ make_shared<SolidColour>(c2) }
	{

	}

	virtual Colour Value(double u, double v, const Point3& p) const override
	{
		int uu = u * 100;
		int vv = v * 100;

		uu /= m_frequency;
		vv /= m_frequency;

		if (vv % 2)
		{
			if (uu % 2) return m_odd->Value(u, v, p);
			else return m_even->Value(u, v, p);
		}
		else
		{
			if (uu % 2) return m_even->Value(u, v, p);
			else return m_odd->Value(u, v, p);
		}
	}

	void SetFrequency(int freq)
	{
		m_frequency = freq;
	}

private:
	shared_ptr<Texture> m_even;
	shared_ptr<Texture> m_odd;
	int m_frequency{ 2 };

};

#endif