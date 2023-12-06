/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** BoundingBoxes
*/

#include "BoundingBoxes.hpp"

namespace RayTracer {
    BoundingBoxes::BoundingBoxes() {
    }

    BoundingBoxes::BoundingBoxes(const Math::Vector3 &min, const Math::Vector3 &max) {
        minimum = min;
        maximum = max;
    }

    BoundingBoxes::~BoundingBoxes() {
    }

    Math::Vector3 BoundingBoxes::min() const {
        return minimum;
    }

    Math::Vector3 BoundingBoxes::max() const {
        return maximum;
    }

    bool BoundingBoxes::hit(const Ray &ray, double t_min, double t_max) const {
        for (int a = 0; a < 3; a++) {
            auto invD = 1.0 / ray.direction[a];
            auto t0 = (minimum[a] - ray.origin[a]) * invD;
            auto t1 = (maximum[a] - ray.origin[a]) * invD;
            if (invD < 0.0)
                std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min)
                return false;
        }
        return true;
    }

    BoundingBoxes surroundingBox(BoundingBoxes box1, BoundingBoxes box2) {
        Math::Vector3 small(fmin(box1.min().x, box2.min().x),
                            fmin(box1.min().y, box2.min().y),
                            fmin(box1.min().z, box2.min().z));
        Math::Vector3 big(fmax(box1.max().x, box2.max().x),
                        fmax(box1.max().y, box2.max().y),
                        fmax(box1.max().z, box2.max().z));
        return BoundingBoxes(small, big);
    }
}  // namespace RayTracer
