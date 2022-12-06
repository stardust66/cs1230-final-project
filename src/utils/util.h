#pragma once

#include "rgba.h"
#include <cmath>
#include <glm/glm.hpp>
#include <qimage.h>
#include <stdint.h>

template <typename T> bool isBetween(T x, T a, T b) {
    return a <= x && x <= b;
}

uint8_t clampColor(float color);

RGBA toRGBA(const auto& v) {
    return RGBA{clampColor(v.x), clampColor(v.y), clampColor(v.z)};
}

glm::vec4 wrapNormal(const glm::vec3& normal);

QImage loadImageFromFile(const std::string& filename);

RGBA getPixelFromQImage(int i, int j, const QImage& image);

float getPercentangeAroundPerimeter(const glm::vec4& pos);
