#include "raytracescene.h"
#include "raytracer/shapes/sphere.h"
#include "utils/sceneparser.h"

namespace {
const SceneMaterial RED_MATERIAL = {
    .cDiffuse = {1, 0, 0, 1},
    .cSpecular = {1, 1, 1, 1},
    .shininess = 25,
};

std::vector<std::unique_ptr<SDFShape>> makeShapes() {
    auto result = std::vector<std::unique_ptr<SDFShape>>{};
    result.emplace_back(std::make_unique<Sphere>(glm::vec4{0, 0, 0, 1}, 0.25, RED_MATERIAL));
    return result;
}
} // namespace

RayTraceScene::RayTraceScene(int width, int height, const RenderData& metaData)
    : w(width), h(height), camera(metaData.cameraData, (float)width / height),
      globalData(metaData.globalData), lights(metaData.lights), shapes(makeShapes()) {}

const int& RayTraceScene::width() const {
    return w;
}

const int& RayTraceScene::height() const {
    return h;
}

const SceneGlobalData& RayTraceScene::getGlobalData() const {
    return globalData;
}

const Camera& RayTraceScene::getCamera() const {
    return camera;
}

const std::vector<std::unique_ptr<SDFShape>>& RayTraceScene::getShapes() const {
    return shapes;
}

const std::vector<SceneLightData>& RayTraceScene::getLights() const {
    return lights;
}
