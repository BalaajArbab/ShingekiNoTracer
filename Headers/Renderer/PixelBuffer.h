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
    using byte4 = double;

private:
    byte4* m_rgbs;
    byte* m_bytes{};

    int m_width;
    int m_height;

    int m_count{ 0 };

public:
    PixelBuffer() = default;

    PixelBuffer(int width, int height) : m_rgbs{ new byte4[width * height * 3] }, m_width{ width }, m_height{ height }
    {

    }

    ~PixelBuffer()
    {
        delete[] m_rgbs;
        delete[] m_bytes;
    }

    PixelBuffer(const PixelBuffer& pb) = delete;

    PixelBuffer& operator=(const PixelBuffer& pb) = delete;

    void InitializeBuffer(int width, int height)
    {
        m_rgbs = new byte4[width * height * 3]{};
        m_width = width;
        m_height = height;
    }

    void AddRGBTriplet(byte4 r, byte4 g, byte4 b)
    {
        assert(m_count < (m_width * m_height));

        m_rgbs[m_count * 3] = r;
        m_rgbs[m_count * 3 + 1] = g;
        m_rgbs[m_count * 3 + 2] = b;

        //std::cout << "PB: " << (int)m_rgbs[m_count * 3] << ' ' << (int)m_rgbs[m_count * 3 + 1] << ' ' << (int)m_rgbs[m_count * 3 + 2] << '\n';

        ++m_count;
    }

    void AddColour(const Colour& c)
    {
        AddRGBTriplet(c.X(), c.Y(), c.Z());
    }

    void Clear()
    {
        m_count = 0;
    }

    void* Data()
    {
        return m_bytes;
    }

    void AveragePixelBuffers(PixelBuffer pbs[], int pbsN, int totalSamples)
    {
        m_bytes = new byte[m_width * m_height * 3];

        for (int i = 0; i < pbsN; ++i)
        {
            for (int b = 0; b < m_width * m_height * 3; b += 3)
            {
                m_rgbs[b + 0] += pbs[i].m_rgbs[b + 0];
                m_rgbs[b + 1] += pbs[i].m_rgbs[b + 1];
                m_rgbs[b + 2] += pbs[i].m_rgbs[b + 2];
            }
        }

        for (int b = 0; b < m_width * m_height * 3; b += 3)
        {
            double red = m_rgbs[b + 0];
            double green = m_rgbs[b + 1];
            double blue = m_rgbs[b + 2];

            double scale = 1.0 / totalSamples;
            red *= scale;
            green *= scale;
            blue *= scale;

            // Gamma2 Correction
            red = sqrt(red);
            green = sqrt(green);
            blue = sqrt(blue);

            red = 256 * Clamp(red, 0.0, 0.999);
            green = 256 * Clamp(green, 0.0, 0.999);
            blue = 256 * Clamp(blue, 0.0, 0.999);

            m_bytes[b + 0] = red;
            m_bytes[b + 1] = green;
            m_bytes[b + 2] = blue;

        }

        m_count = m_width * m_height;
    }

};

#endif

