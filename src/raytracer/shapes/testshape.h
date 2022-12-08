#pragma once

#include "raytracer/sdfshape.h"

/**
 * Use this class to experiment with SDFs
 */
class TestShape : public SDFShape {
  public:
    TestShape(SceneMaterial material);

  private:
    float sdf(const glm::vec4& point) const override;
};
