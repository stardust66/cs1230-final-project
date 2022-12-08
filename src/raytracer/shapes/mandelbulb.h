#pragma once

#include "raytracer/sdfshape.h"

class Mandelbulb : public SDFShape {
  public:
    Mandelbulb(SceneMaterial material);

  private:
    float sdf(const glm::vec4& point) const override;
};
