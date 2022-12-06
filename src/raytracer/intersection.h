#pragma once

#include "utils/scenedata.h"
#include <glm/glm.hpp>

struct Intersection {
    float t;
    glm::vec4 normal;
    glm::vec4 position;
    const SceneMaterial* material;

    friend bool operator<=(const Intersection& i1, const Intersection& i2);
};
