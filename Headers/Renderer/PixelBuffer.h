#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <cassert>
#include <cstdint>

#include <Math/Vector3.h>
#include <Utility/Utility.h>


class PixelBuffer
{
public:
    using byte = std::uint8_t;

private:
    byte* const m_rgbs;

    const int m_width;
    const int m_height;

    int m_count{ 0 };

public:
    PixelBuffer(int width, int height) : m_rgbs{ new byte[width * height * 3] }, m_width{ width }, m_height{ height }
    {

    }

    ~PixelBuffer()
    {
        delete[] m_rgbs;
    }

    PixelBuffer(const PixelBuffer& pb) = delete;

    PixelBuffer& operator=(const PixelBuffer& pb) = delete;

    void AddRGBTriplet(byte r, byte g, byte b)
    {
        assert(m_count < (m_width * m_height));

        m_rgbs[m_count * 3] = r;
        m_rgbs[m_count * 3 + 1] = g;
        m_rgbs[m_count * 3 + 2] = b;

        //std::cout << "PB: " << (int)m_rgbs[m_count * 3] << ' ' << (int)m_rgbs[m_count * 3 + 1] << ' ' << (int)m_rgbs[m_count * 3 + 2] << '\n';

        ++m_count;
    }

    void AddColour(const Colour& c, const std::int32_t samplesPerPixel)
    {
        double r = c.X();
        double g = c.Y();
        double b = c.Z();

        double scale = 1.0 / samplesPerPixel;
        r *= scale;
        g *= scale;
        b *= scale;

        // Gamma2 Correction
        r = sqrt(r);
        g = sqrt(g);
        b = sqrt(b);

        r = 256 * Clamp(r, 0.0, 0.999);
        g = 256 * Clamp(g, 0.0, 0.999);
        b = 256 * Clamp(b, 0.0, 0.999);

        AddRGBTriplet(r, g, b);
    }

    void Clear()
    {
        m_count = 0;
    }

    void* Data()
    {
        return m_rgbs;
    }

};

#endif

