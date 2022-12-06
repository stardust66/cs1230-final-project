#pragma once

#include "raytracer/intersection.h"
#include "raytracer/ray.h"
#include <optional>

class Intersect {
  public:
    Intersect(SceneMaterial material);
    virtual std::optional<Intersection> intersect(const Ray& ray) const = 0;

  protected:
    SceneMaterial material;
};
