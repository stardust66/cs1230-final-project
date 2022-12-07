#pragma once

#include "raytracer/sdfshape.h"

class Torus : public SDFShape {
  public:
    Torus(float outerRadius, float innerRadius, SceneMaterial material);

  private:
    float outerRadius;
    float innerRadius;

    float sdf(const glm::vec4& point) const override;
};
