#ifndef SHINGEKINOTRACER_H
#define SHINGEKINOTRACER_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstddef>
#include <string>

#include <Utility/Stopwatch.h>
#include <Utility/Utility.h>
#include <Utility/stb_image_write.h>

#include <Math/Vector3.h>

#include <Renderer/PixelBuffer.h>
#include <Renderer/HittableList.h>
#include <Renderer/Camera.h>
#include <Renderer/Image.h>

#include <Shapes/Sphere.h>

#include <Materials/Material.h>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>

#endif
