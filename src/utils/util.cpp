#include "utils/util.h"
#include <numbers>

uint8_t clampColor(float color) {
    return 255 * fmax(fmin(color, 1), 0);
}

glm::vec4 wrapNormal(const glm::vec3& normal) {
    return glm::vec4(normal.x, normal.y, normal.z, 0);
}

QImage loadImageFromFile(const std::string& filename) {
    QImage image{QString::fromStdString(filename)};
    if (image.isNull()) {
        throw std::invalid_argument("Filename invalid");
    }
    image = image.convertToFormat(QImage::Format_RGBX8888);
    return image;
}

RGBA getPixelFromQImage(int i, int j, const QImage& image) {
    const auto& raw = image.bits();
    auto index = j * image.width() + i;
    return RGBA{raw[4 * index], raw[4 * index + 1], raw[4 * index + 2], raw[4 * index + 3]};
}

float getPercentangeAroundPerimeter(const glm::vec4& pos) {
    auto theta = atan2(pos.z, pos.x);
    auto thetaOverTwoPi = theta / (2 * std::numbers::pi);
    if (theta < 0) {
        return -thetaOverTwoPi;
    } else {
        return 1 - thetaOverTwoPi;
    }
}
