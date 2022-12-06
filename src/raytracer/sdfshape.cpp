#include "sdfshape.h"
#include <array>
#include <iostream>

SDFShape::SDFShape(SceneMaterial material) : Intersect(material) {}

const int MAX_RAYMARCH_ITERATION = 1000;
const float RAYMARCH_STEP_RATIO = 0.01;
const float RAYMARCH_THRESHOLD = 1;
std::optional<Intersection> SDFShape::intersect(const Ray& ray) const {
    auto currentPosition = ray.origin;
    for (auto iterationCount = 0; iterationCount < MAX_RAYMARCH_ITERATION; ++iterationCount) {
        auto distanceToClosestPoint = sdf(currentPosition);

        if (distanceToClosestPoint < RAYMARCH_THRESHOLD) {
            return Intersection{.t = glm::distance(currentPosition, ray.origin),
                                .normal = computeSdfNormal(currentPosition),
                                .position = currentPosition,
                                .material = &material};
        }

        // March along the ray's direction by a proportion of the computed distance, so we don't
        // overshoot
        currentPosition += RAYMARCH_STEP_RATIO * distanceToClosestPoint * ray.direction;
    }

    // No intersection found
    return std::nullopt;
}

const float EPSILON = 0.00001;
const auto EPSILON_VECTORS = std::array<glm::vec4, 3>{
    glm::vec4{EPSILON, 0, 0, 0},
    glm::vec4{0, EPSILON, 0, 0},
    glm::vec4{0, 0, EPSILON, 0},
};
glm::vec4 SDFShape::computeSdfNormal(const glm::vec4& point) const {
    auto normal = glm::vec4{0, 0, 0, 0};
    for (auto i = 0; i < 3; ++i) {
        normal[i] = sdf(point + EPSILON_VECTORS[i]) - sdf(point - EPSILON_VECTORS[i]);
    }
    return glm::normalize(normal);
}
