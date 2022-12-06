#include "sceneparser.h"
#include "glm/gtx/transform.hpp"
#include "scenefilereader.h"

namespace {
glm::mat4 getSceneTransformationMatrix(const SceneTransformation& transform) {
    switch (transform.type) {
    case TransformationType::TRANSFORMATION_TRANSLATE:
        return glm::translate(transform.translate);
    case TransformationType::TRANSFORMATION_SCALE:
        return glm::scale(transform.scale);
    case TransformationType::TRANSFORMATION_ROTATE:
        return glm::rotate(transform.angle, transform.rotate);
    case TransformationType::TRANSFORMATION_MATRIX:
        return transform.matrix;
    default:
        // Should never be reached since handling of enum values above is exhaustive
        return transform.matrix;
    }
}

void parseSceneGraphAndAppend(std::vector<RenderShapeData>& shapes, SceneNode* rootNode) {
    auto identity = glm::mat4(1);
    std::function<void(SceneNode*, glm::mat4&)> dfs = [&](SceneNode* node,
                                                          const glm::mat4& currentCTM) {
        // New cumulative transformation matrix, which apply to the primitives of the current node
        // as well as all children
        auto newCTM = currentCTM;
        for (const auto& transform : node->transformations) {
            newCTM *= getSceneTransformationMatrix(*transform);
        }

        // Primitives
        for (const auto& shape : node->primitives) {
            auto shapeData = RenderShapeData{*shape, newCTM};
            shapes.push_back(shapeData);
        }

        // Children
        for (const auto& childNode : node->children) {
            dfs(childNode, newCTM);
        }
    };
    dfs(rootNode, identity);
}
} // namespace

bool SceneParser::parse(std::string filepath, RenderData& renderData) {
    ScenefileReader fileReader = ScenefileReader(filepath);
    bool success = fileReader.readXML();
    if (!success) {
        return false;
    }

    renderData.globalData = fileReader.getGlobalData();
    renderData.lights = fileReader.getLights();
    renderData.cameraData = fileReader.getCameraData();

    auto rootNode = fileReader.getRootNode();
    renderData.shapes.clear();
    parseSceneGraphAndAppend(renderData.shapes, rootNode);

    return true;
}

RenderShapeData::RenderShapeData(ScenePrimitive& primitive, glm::mat4& ctm)
    : primitive(primitive), ctm(ctm), inverseCtm(glm::inverse(ctm)),
      inverseTransposeCtm(glm::inverse(glm::transpose(glm::mat3(ctm)))) {}
