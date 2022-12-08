#include "testshape.h"

TestShape::TestShape(SceneMaterial material): SDFShape(material) {}

float TestShape::sdf(const glm::vec4& point) const {
    // Field of spheres
    auto a = glm::mod(point.xz(), 1.0f) - 0.5f;
    return glm::length(glm::vec3{a.x, point.y, a.y}) - 0.3;
}
