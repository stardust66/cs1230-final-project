#include "raytracer.h"
#include "phong.h"
#include "ray.h"
#include "raytracescene.h"
#include "utils/util.h"
#include <iostream>
#include <optional>
#include <unordered_map>

RayTracer::RayTracer(Config config) : m_config(config) {}

void RayTracer::render(RGBA* imageData, const RayTraceScene& scene) {
    auto& camera = scene.getCamera();
    auto width = scene.width();
    auto height = scene.height();

    // Raytrace each pixel
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            auto ray = makeRay(i, j, width, height, camera);

            // Find intersection with smallest t
            std::optional<Intersection> intersection;
            for (auto& shape : scene.getShapes()) {
                auto shapeIntersection = shape->intersect(ray);
                if (!intersection) {
                    intersection = shapeIntersection;
                    continue;
                }
                if (shapeIntersection && *shapeIntersection <= *intersection) {
                    intersection = shapeIntersection;
                }
            }

            if (intersection) {
                auto directionToCamera =
                    glm::normalize(camera.getPosition() - intersection->position);
                imageData[j * width + i] =
                    toRGBA(phong(*intersection, scene, directionToCamera, m_config));
            }
        }
    }
}
