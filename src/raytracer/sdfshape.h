#pragma once

#include "raytracer/intersection.h"
#include "raytracer/ray.h"
#include <glm/glm.hpp>
#include <memory>
#include <optional>

class SDFShape {
  public:
    SDFShape(SceneMaterial material);
    virtual ~SDFShape(){};

    virtual float sdf(const glm::vec4& point) const = 0;

    glm::vec4 computeSdfNormal(const glm::vec4& point) const;

    SceneMaterial material;
};

std::optional<Intersection>
intersectSDFShapes(const Ray& ray, const std::vector<std::unique_ptr<SDFShape>>& shapes);

std::tuple<float, const SDFShape*>
getMinDistanceFromSDFs(const glm::vec4& point,
                       const std::vector<std::unique_ptr<SDFShape>>& shapes);
