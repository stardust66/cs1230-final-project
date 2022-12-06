#include "camera.h"
#include <stdexcept>

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}

glm::mat4 Camera::getInverseViewMatrix() const {
    return inverseViewMatrix;
}

float Camera::getAspectRatio() const {
    return aspectRatio;
}

float Camera::getHeightAngle() const {
    return heightAngle;
}

float Camera::getFocalLength() const {
    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}

float Camera::getAperture() const {
    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}

Camera::Camera(const SceneCameraData& data, float aspectRatio)
    : heightAngle(data.heightAngle), aspectRatio(aspectRatio), position(data.pos) {
    auto w = -glm::normalize(data.look);
    auto v = glm::normalize(data.up - glm::dot(data.up, w) * w);
    auto u = glm::cross(glm::vec3(v), glm::vec3(w));
    viewMatrix = glm::mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, -data.pos.x,
                           -data.pos.y, -data.pos.z, 1);
    inverseViewMatrix = glm::inverse(viewMatrix);
}

glm::vec4 Camera::getPosition() const {
    return position;
}
