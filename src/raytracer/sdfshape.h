#pragma once

#include <glm/glm.hpp>
#include "raytracer/intersect.h"
#include "raytracer/intersection.h"
#include "raytracer/ray.h"

class SDFShape : public Intersect {
    public:
        SDFShape(SceneMaterial material);

        std::optional<Intersection> intersect(const Ray& ray) const override;

    private:
        glm::vec4 computeSdfNormal(const glm::vec4& point) const;

        virtual float sdf(const glm::vec4& point) const = 0;
};
