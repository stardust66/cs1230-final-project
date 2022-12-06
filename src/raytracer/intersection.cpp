#include "raytracer/intersection.h"

bool operator<=(const Intersection& i1, const Intersection& i2) {
    return i1.t <= i2.t;
}
