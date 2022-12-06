#include "ray.h"

glm::vec4 getRayDirectionInWorldSpace(int i, int j, int width, int height, const Camera& camera) {
    auto viewPlaneHeight = 2 * tan(camera.getHeightAngle() / 2);
    auto viewPlaneWidth = viewPlaneHeight * camera.getAspectRatio();
    auto x = viewPlaneWidth * ((i + 0.5) / width - 0.5);
    auto y = viewPlaneHeight * ((height - 1 - j + 0.5) / height - 0.5);
    auto d = glm::vec4(x, y, -1, 0);
    return glm::normalize(camera.getInverseViewMatrix() * d);
}

Ray makeRay(int i, int j, int width, int height, const Camera& camera) {
    auto rayDirection = getRayDirectionInWorldSpace(i, j, width, height, camera);
    return Ray{.origin = camera.getPosition(), .direction = rayDirection};
}
