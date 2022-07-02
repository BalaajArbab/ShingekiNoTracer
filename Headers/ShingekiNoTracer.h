#ifndef SHINGEKINOTRACER_H
#define SHINGEKINOTRACER_H

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <cstddef>
#include <string>


#include <Utility/Utility.h>

// Disable Pedantic Warnings
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )

#include <stb_image_write.h>
#include <Utility/Stopwatch.h>

// Restore warning levels.
#pragma warning( pop )

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
#include <Shapes/Fractal.h>

#include <Materials/Material.h>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>
#include <Materials/DiffuseLight.h>

#include <Textures/Texture.h>
#include <Textures/CheckerTexture.h>

#include <Scenes.h>

#include <Parallel.h>
#include <thread>
#include <mutex>

#endif
