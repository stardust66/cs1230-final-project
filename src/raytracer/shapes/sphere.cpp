#include "sphere.h"

Sphere::Sphere(glm::vec4 origin, float radius, SceneMaterial material)
    : SDFShape(material), origin(origin), radius(radius) {}

float Sphere::sdf(const glm::vec4& point) const {
    return glm::distance(origin, point) - radius;
}
