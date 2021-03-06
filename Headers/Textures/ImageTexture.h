#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include <ImageIO.h>

#include <Textures/Texture.h>

class ImageTexture : public Texture
{
public:
	using byte = std::uint8_t;

	const static byte bytesPerPixel = 3;

	ImageTexture()
		: m_data{ nullptr }, m_width{ 0 }, m_height{ 0 }, m_bytesPerScanline{ 0 }, m_unGammaCorrect{ true }
	{

	}

	ImageTexture(const char* filename, bool unGamma = true)
		: m_unGammaCorrect{ unGamma }
	{
		int componentsPerPixel = bytesPerPixel;

		m_data = stbi_load(filename, &m_width, &m_height, &componentsPerPixel, componentsPerPixel);

		if (!m_data)
		{
			std::cout << "Could not load texture image file: " << filename << '\n';
			m_width = 0;
			m_height = 0;
		}

		m_bytesPerScanline = m_width * bytesPerPixel;
	}

	~ImageTexture()
	{
		delete[] m_data;
	}

	virtual Colour Value(double u, double v, const Point3& p) const override;


private:
	byte* m_data;
	int m_width;
	int m_height;
	int m_bytesPerScanline;
	bool m_unGammaCorrect;

};

inline Colour ImageTexture::Value(double u, double v, const Point3& p) const
{
	// If we have no texture data, then return solid cyan as a debugging aid.
	if (!m_data)
	{
		return Colour{ 0, 1, 1 };
	}

	// Clamp input texture coordinates to [1,0] x [0,1]
	u = Clamp(u, 0.0, 1.0);
	v = 1 - Clamp(v, 0.0, 1.0);  // Flip V to image coordinates

	int xOfImage = u * m_width;
	int yOfImage = v * m_height;

	// Clamp integer mapping, since actual coordinates should be less than 1.0
	if (xOfImage >= m_width) xOfImage = m_width - 1;
	if (yOfImage >= m_height) yOfImage = m_height - 1;

	const double colourScale = 1.0 / 255.0;

	byte* pixel = m_data + (xOfImage * bytesPerPixel) + (yOfImage * m_bytesPerScanline);

	double r = colourScale * pixel[0];
	double g = colourScale * pixel[1];
	double b = colourScale * pixel[2];

	if (m_unGammaCorrect)
	{
		r = r * r;
		g = g * g;
		b = b * b;
	}


	return Colour{ r, g, b };
}

#endif