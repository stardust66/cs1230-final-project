#include "phong.h"
#include "raytracer/ray.h"
#include "utils/scenedata.h"
#include "utils/util.h"
#include <stdexcept>

namespace {
glm::vec4 getDirectionFromLight(const SceneLightData& light, const glm::vec4& position) {
    switch (light.type) {
    case LightType::LIGHT_DIRECTIONAL:
        return glm::normalize(light.dir);
    case LightType::LIGHT_POINT:
    case LightType::LIGHT_SPOT:
        return glm::normalize(position - light.pos);
    default:
        throw std::invalid_argument("Unsupported light type");
    }
}

float getAttenuation(const SceneLightData& light, const glm::vec4& position) {
    if (light.type == LightType::LIGHT_DIRECTIONAL) {
        // Directional light is infinitely far away, so attenuation does not make sense
        return 1;
    }
    auto distance = glm::length(position - light.pos);
    auto c1 = light.function.x;
    auto c2 = light.function.y;
    auto c3 = light.function.z;
    return fmin(1, 1 / (c1 + distance * c2 + pow(distance, 2) * c3));
}

Ray makeShiftedRay(const glm::vec4& position, const glm::vec4& direction) {
    return Ray{.origin = position + 0.001f * direction, .direction = direction};
}

float getSpotLightFalloff(const SceneLightData& light, const glm::vec4& directionFromLight) {
    if (light.type != LightType::LIGHT_SPOT) {
        return 1;
    }
    auto angleBetween = acos(glm::dot(glm::normalize(light.dir), directionFromLight));
    auto inner = light.angle - light.penumbra;
    if (angleBetween > light.angle) {
        return 0;
    }
    if (angleBetween <= inner) {
        return 1;
    }
    auto x = (angleBetween - inner) / light.penumbra;
    return 1 - (-2 * pow(x, 3) + 3 * pow(x, 2));
}

std::pair<int, int> getImageCoordsFromUV(float u, float v, float repeatU, float repeatV, int width,
                                         int height) {
    return {(int)floor(u * repeatU * width) % width,
            (int)floor((1 - v) * repeatV * height) % height};
}

template <typename T> T interpolate(T a, T b, float t) {
    return (1 - t) * a + t * b;
}

glm::vec4 getQImageColorAt(const QImage& image, int x, int y) {
    const auto* rawImage = image.constBits();
    auto startOffset = 4 * (y * image.width() + x);
    return glm::vec4{(float)rawImage[startOffset] / 255, (float)rawImage[startOffset + 1] / 255,
                     (float)rawImage[startOffset + 2] / 255, 1};
}
} // namespace

glm::vec4 shade(const Intersection& intersection, const RayTraceScene& scene,
                const glm::vec4& directionToCamera, const RayTracer::Config& config,
                int reflectionDepth) {
    const auto& globalData = scene.getGlobalData();
    const auto& material = *intersection.material;

    // Normalizing directions
    auto normal = glm::normalize(intersection.normal);

    // Output illumination (we can ignore opacity)
    glm::vec4 illumination(0, 0, 0, 1);

    // Add the ambient term
    illumination += globalData.ka * material.cAmbient;

    for (const auto& light : scene.getLights()) {
        // Area light not supported
        if (light.type == LightType::LIGHT_AREA) {
            continue;
        }

        auto directionFromLight = getDirectionFromLight(light, intersection.position);

        auto shadowRay = Ray{.origin = intersection.position - 0.01f * directionFromLight,
                             .direction = -directionFromLight};
        if (intersectSDFShapes(shadowRay, scene.getShapes())) {
            continue;
        }

        // Add the diffuse term, where the color is blended with a texture
        auto diffuse =
            globalData.kd * material.cDiffuse * fmaxf(glm::dot(normal, -directionFromLight), 0);

        // Add the specular term
        auto reflectionDirection = glm::normalize(glm::reflect(directionFromLight, normal));
        auto specular =
            globalData.ks * material.cSpecular *
            powf(fmaxf(0, glm::dot(reflectionDirection, directionToCamera)), material.shininess);

        auto attenuationFactor = getAttenuation(light, intersection.position);
        auto spotLightFalloff = getSpotLightFalloff(light, directionFromLight);
        illumination += light.color * spotLightFalloff * attenuationFactor * (diffuse + specular);
    }

    return illumination;
}
