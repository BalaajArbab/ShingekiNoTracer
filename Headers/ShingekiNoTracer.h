#ifndef SHINGEKINOTRACER_H
#define SHINGEKINOTRACER_H

#include <iostream>
#include <cstddef>
#include <string>

#include <Utility/Stopwatch.h>
#include <Utility/Utility.h>

#include <Math/Vector3.h>

#include <Renderer/PixelBuffer.h>
#include <Renderer/HittableList.h>
#include <Renderer/Camera.h>
#include <Renderer/Image.h>
#include <Renderer/BVHNode.h>

#include <Shapes/Sphere.h>

#include <Materials/Material.h>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>

#include <Textures/Texture.h>
#include <Textures/CheckerTexture.h>

#include <Scenes.h>

#endif
