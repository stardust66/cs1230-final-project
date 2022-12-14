#pragma once

#include "raytracer/intersection.h"
#include "raytracer/raytracer.h"
#include "raytracer/raytracescene.h"
#include <qimage.h>
#include <unordered_map>

// Calculates the RGBA of a pixel from intersection infomation and globally-defined coefficients
glm::vec4 shade(const Intersection& intersection, const RayTraceScene& scene,
                const glm::vec4& directionToCamera, const RayTracer::Config& config,
                int reflectionDepth = 0, int refractionDepth = 0);
