#pragma once

#include "camera/camera.h"
#include <glm/glm.hpp>

struct Ray {
    glm::vec4 origin;
    glm::vec4 direction;

    glm::vec4 getAt(float t) const {
        return origin + t * direction;
    }
};

glm::vec4 getRayDirectionInWorldSpace(int i, int j, int width, int height, const Camera& camera);

Ray makeRay(int i, int j, int width, int height, const Camera& camera);
