#include "torus.h"

Torus::Torus(float outerRadius, float innerRadius, SceneMaterial material)
    : SDFShape(material), outerRadius(outerRadius), innerRadius(innerRadius) {}

// From https://iquilezles.org/articles/distfunctions/
float Torus::sdf(const glm::vec4& point) const {
    auto q = glm::vec2(glm::length(point.xz()) - outerRadius, point.y);
    return glm::length(q) - innerRadius;
}
