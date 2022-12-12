#include "mandelbulb.h"

Mandelbulb::Mandelbulb(SceneMaterial material) : SDFShape(material) {}

const float POWER = 3;
float Mandelbulb::sdf(const glm::vec4& p) const {
    // Convert y-up to z-up
    auto pZUp = glm::vec3{p.x, p.z, p.y};
    auto z = pZUp;
    float dr = 1.0;
    float r = 0.0;
    for (int i = 0; i < 30; i++) {
        r = length(z);
        if (r > 4.0)
            break;

        // Convert to polar coordinates
        float theta = acos(z.z / r);
        float phi = glm::atan(z.y, z.x);
        dr = pow(r, POWER - 1.0) * POWER * dr + 1.0;

        // Scale and rotate the point
        float zr = pow(r, POWER);
        theta = theta * POWER;
        phi = phi * POWER;

        // Convert back to cartesian coordinates
        z = zr * glm::vec3(sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
        z += pZUp;
    }

    return 0.5 * log(r) * r / dr;
}
