#include "plane.h"

Plane::Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, SceneMaterial material)
    : SDFShape(material), a(a), b(b), c(c), d(d) {}

namespace {
float dot2(auto v) {
    return glm::dot(v, v);
}
} // namespace

// From https://iquilezles.org/articles/distfunctions/
float Plane::sdf(const glm::vec4& point) const {
    // Comes from an OpenGL implementation, which uses z-up convention, while we use y-up. Instead
    // of changing the sdf, we use this hack to translate between the two.
    glm::vec3 p = glm::vec3{point.x, point.z, point.y};
    auto ba = b - a;
    auto pa = p - a;
    auto cb = c - b;
    auto pb = p - b;
    auto dc = d - c;
    auto pc = p - c;
    auto ad = a - d;
    auto pd = p - d;
    auto nor = cross(ba, ad);

    // clang-format off
    return sqrt(
        (glm::sign(dot(cross(ba, nor), pa)) +
         glm::sign(dot(cross(cb, nor), pb)) +
         glm::sign(dot(cross(dc, nor), pc)) +
         glm::sign(dot(cross(ad, nor), pd)) < 3.0)
         ?
         fmin(fmin(fmin(
            dot2(ba * glm::clamp(dot(ba, pa) / dot2(ba), 0.0f, 1.0f) - pa),
            dot2(cb * glm::clamp(dot(cb, pb) / dot2(cb), 0.0f, 1.0f) - pb)),
            dot2(dc * glm::clamp(dot(dc, pc) / dot2(dc), 0.0f, 1.0f) - pc)),
            dot2(ad * glm::clamp(dot(ad, pd) / dot2(ad), 0.0f, 1.0f) - pd))
         :
         dot(nor, pa) * dot(nor, pa) / dot2(nor));
    // clang-format on
}
