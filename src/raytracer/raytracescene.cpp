#include "raytracescene.h"
#include "raytracer/intersect.h"
#include "raytracer/shapes/sphere.h"
#include "utils/sceneparser.h"

namespace {
std::vector<std::unique_ptr<Intersect>>
makeShapes(const std::vector<RenderShapeData>& parsedShapes) {
    auto resultShapes = std::vector<std::unique_ptr<Intersect>>{};
    for (const auto& parsedShape : parsedShapes) {
        switch (parsedShape.primitive.type) {
        case PrimitiveType::PRIMITIVE_SPHERE: {
            resultShapes.emplace_back(std::make_unique<Sphere>(glm::vec4{0, 0, 0, 0}, 0.25,
                                                               parsedShape.primitive.material));
        }
        default:
            continue;
        }
    }
    return resultShapes;
}
} // namespace

RayTraceScene::RayTraceScene(int width, int height, const RenderData& metaData)
    : w(width), h(height), camera(metaData.cameraData, (float)width / height),
      globalData(metaData.globalData), lights(metaData.lights),
      shapes(makeShapes(metaData.shapes)) {}

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

const std::vector<std::unique_ptr<Intersect>>& RayTraceScene::getShapes() const {
    return shapes;
}

const std::vector<SceneLightData>& RayTraceScene::getLights() const {
    return lights;
}
