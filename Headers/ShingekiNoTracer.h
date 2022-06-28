#ifndef SHINGEKINOTRACER_H
#define SHINGEKINOTRACER_H

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <cstddef>
#include <string>

#include <Utility/Stopwatch.h>
#include <Utility/Utility.h>

#include <stb_image_write.h>

#include <Math/Vector3.h>

#include <Renderer/PixelBuffer.h>
#include <Renderer/HittableList.h>
#include <Renderer/Camera.h>
#include <Renderer/Image.h>
#include <Renderer/BVHNode.h>

#include <Shapes/Sphere.h>
#include <Shapes/AARects.h>
#include <Shapes/Box.h>
#include <Shapes/Cylinder.h>
#include <Shapes/Translate.h>
#include <Shapes/Rotations.h>

#include <Materials/Material.h>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>
#include <Materials/DiffuseLight.h>

#include <Textures/Texture.h>
#include <Textures/CheckerTexture.h>

#include <Scenes.h>

#endif
