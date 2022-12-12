#include "sierpinski.h"

const float SCALE = 2.0;
const int ITERATIONS = 15;
float Sierpinski::sdf(const glm::vec4& point) const {
    auto z = glm::vec3{point.x, point.z, point.y};
    auto a1 = glm::vec3{1, 1, 1};
    auto a2 = glm::vec3{-1, -1, 1};
    auto a3 = glm::vec3{1, -1, -1};
    auto a4 = glm::vec3{-1, 1, -1};
    glm::vec3 c;
    int n = 0;
    float dist, d;
    while (n < ITERATIONS) {
        c = a1;
        dist = glm::length(z - a1);
        d = glm::length(z - a2);
        if (d < dist) {
            c = a2;
            dist = d;
        }
        d = glm::length(z - a3);
        if (d < dist) {
            c = a3;
            dist = d;
        }
        d = glm::length(z - a4);
        if (d < dist) {
            c = a4;
            dist = d;
        }
        z = SCALE * z - c * (SCALE - 1.0f);
        n++;
    }

    return glm::length(z) * pow(SCALE, float(-n));
}
