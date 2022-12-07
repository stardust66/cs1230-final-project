#pragma once

#include "camera/camera.h"
#include "raytracer/sdfshape.h"
#include "utils/scenedata.h"
#include "utils/sceneparser.h"
#include <memory>

// A class representing a scene to be ray-traced

// Feel free to make your own design choices for RayTraceScene, the functions below are all optional
// / for your convenience. You can either implement and use these getters, or make your own design.
// If you decide to make your own design, feel free to delete these as TAs won't rely on them to
// grade your assignments.

class RayTraceScene {
  public:
    RayTraceScene(int width, int height, const RenderData& metaData);

    // The getter of the width of the scene
    const int& width() const;

    // The getter of the height of the scene
    const int& height() const;

    // The getter of the global data of the scene
    const SceneGlobalData& getGlobalData() const;

    // The getter of the shared pointer to the camera instance of the scene
    const Camera& getCamera() const;

    const std::vector<std::unique_ptr<SDFShape>>& getShapes() const;

    const std::vector<SceneLightData>& getLights() const;

  private:
    Camera camera;
    int w;
    int h;
    SceneGlobalData globalData;
    std::vector<SceneLightData> lights;
    std::vector<std::unique_ptr<SDFShape>> shapes;
};
