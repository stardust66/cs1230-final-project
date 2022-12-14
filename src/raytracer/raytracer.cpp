#include "raytracer.h"
#include "phong.h"
#include "ray.h"
#include "raytracescene.h"
#include "utils/util.h"
#include <QThreadPool>
#include <iostream>
#include <optional>

RayTracer::RayTracer(Config config) : m_config(config) {}

void RayTracer::render(RGBA* imageData, const RayTraceScene& scene) {
    auto& camera = scene.getCamera();
    auto width = scene.width();
    auto height = scene.height();

    // Spawn a task for every row of the image
    for (int j = 0; j < height; j++) {
        // Need to capture j by value, otherwise it may mutate before the task runs
        auto task = QRunnable::create([&, j]() {
            for (int i = 0; i < width; i++) {
                auto ray = makeRay(i, j, width, height, camera);

                auto intersection = intersectSDFShapes(ray, scene.getShapes());

                if (intersection) {
                    auto directionToCamera =
                        glm::normalize(camera.getPosition() - intersection->position);
                    imageData[j * width + i] =
                        toRGBA(shade(*intersection, scene, directionToCamera, m_config));
                }
            }
        });
        QThreadPool::globalInstance()->start(task);
    }

    QThreadPool::globalInstance()->waitForDone();
}
