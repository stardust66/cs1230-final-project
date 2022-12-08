#include "sdfshape.h"
#include <array>
#include <iostream>
#include <limits>
#include <tuple>

SDFShape::SDFShape(SceneMaterial material) : material(material) {}

const int MAX_RAYMARCH_ITERATION = 1000;
const float RAYMARCH_HIT_THRESHOLD = 0.001;
const float RAYMARCH_MAX_DISTANCE = 1000;
std::optional<Intersection>
intersectSDFShapes(const Ray& ray, const std::vector<std::unique_ptr<SDFShape>>& shapes) {
    float t = 0;
    for (auto iterationCount = 0; iterationCount < MAX_RAYMARCH_ITERATION; ++iterationCount) {
        auto currentPosition = ray.getAt(t);

        // Get minimum distance from all sdfs
        auto [minDistance, hitShape] = getMinDistanceFromSDFs(currentPosition, shapes);

        if (minDistance < RAYMARCH_HIT_THRESHOLD) {
            return Intersection{
                .t = t,
                .normal = hitShape->computeSdfNormal(currentPosition),
                .position = currentPosition,
                .material = &hitShape->material,
            };
        }

        if (minDistance > RAYMARCH_MAX_DISTANCE) {
            return std::nullopt;
        }

        t += minDistance;
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

std::tuple<float, const SDFShape*>
getMinDistanceFromSDFs(const glm::vec4& point,
                       const std::vector<std::unique_ptr<SDFShape>>& shapes) {
    // Get minimum distance from all sdfs
    float minDistance = std::numeric_limits<float>().max();
    const SDFShape* hitShape = nullptr;
    for (const auto& shape : shapes) {
        auto distanceToShape = shape->sdf(point);
        if (distanceToShape < minDistance) {
            minDistance = distanceToShape;
            hitShape = shape.get();
        }
    }
    return {minDistance, hitShape};
}
