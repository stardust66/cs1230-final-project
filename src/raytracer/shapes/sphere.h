#pragma once

#include "raytracer/sdfshape.h"

class Sphere : public SDFShape {
  public:
    Sphere(glm::vec4 origin, float radius, SceneMaterial material);

  private:
    glm::vec4 origin;
    float radius;

    float sdf(const glm::vec4& point) const override;
};
