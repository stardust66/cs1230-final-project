#include "raytracescene.h"
#include "raytracer/shapes/mandelbulb.h"
#include "raytracer/shapes/plane.h"
#include "raytracer/shapes/sphere.h"
#include "raytracer/shapes/testshape.h"
#include "raytracer/shapes/torus.h"
#include "utils/sceneparser.h"
#include <numbers>

namespace {
const SceneMaterial RED_MATERIAL = {
    .cDiffuse = {1, 0, 0, 1},
    .cSpecular = {1, 1, 1, 1},
    .shininess = 25,
};

const float GREY_FACTOR = 0.1;
const SceneMaterial GRAY_MATERIAL = {
    .cAmbient = {GREY_FACTOR, GREY_FACTOR, GREY_FACTOR, 1},
    .cDiffuse = {GREY_FACTOR, GREY_FACTOR, GREY_FACTOR, 1},
    .cSpecular = {1, 1, 1, 1},
    .shininess = 0,
};

std::vector<std::unique_ptr<SDFShape>> makeShapes() {
    auto result = std::vector<std::unique_ptr<SDFShape>>{};
    //result.emplace_back(std::make_unique<Sphere>(glm::vec4{0, 0.25, 0, 1}, 0.25, RED_MATERIAL));
    //result.emplace_back(std::make_unique<Sphere>(glm::vec4{1, 0, 0, 1}, 0.25, RED_MATERIAL));
    //result.emplace_back(std::make_unique<Sphere>(glm::vec4{0, 0, 1, 1}, 0.25, RED_MATERIAL));
    //result.emplace_back(std::make_unique<Torus>(0.5, 0.1, RED_MATERIAL));
    //result.emplace_back(std::make_unique<Mandelbulb>(RED_MATERIAL));
    result.emplace_back(std::make_unique<TestShape>(RED_MATERIAL));
    result.emplace_back(std::make_unique<Plane>(glm::vec3{-5, 5, -0.25}, glm::vec3{5, 5, -0.25},
                                                glm::vec3{5, -5, -0.25}, glm::vec3{-5, -5, -0.25},
                                                GRAY_MATERIAL));
    return result;
}

/**
 * Use this to ignore parsed camera data and tweak
 */
SceneCameraData makeCameraData() {
    const auto pos = glm::vec4{10, 10, 10, 1};
    const auto focus = glm::vec4{0, 0, 0, 1};
    return SceneCameraData{
        .pos = pos,
        .look = focus - pos,
        .up = {0, 1, 0, 0},
        .heightAngle = std::numbers::pi / 6,
    };
}
} // namespace

RayTraceScene::RayTraceScene(int width, int height, const RenderData& metaData)
    : w(width), h(height), camera(makeCameraData(), (float)width / height),
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
