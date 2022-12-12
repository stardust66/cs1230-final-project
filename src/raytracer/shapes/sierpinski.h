#pragma once

#include "raytracer/sdfshape.h"

class Sierpinski : public SDFShape {
  public:
    Sierpinski(SceneMaterial material) : SDFShape(material) {}

  private:
    float sdf(const glm::vec4& point) const override;
};
