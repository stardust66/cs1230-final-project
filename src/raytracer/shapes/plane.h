#pragma once

#include "raytracer/sdfshape.h"

class Plane : public SDFShape {
  public:
    Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, SceneMaterial material);

  private:
    // Four corners
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
    glm::vec3 d;

    float sdf(const glm::vec4& position) const override;
};
