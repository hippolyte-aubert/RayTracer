/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Glass
*/

#include "Glass.hpp"

namespace RayTracer {
    Glass::Glass(double refractiveIndex) : refractiveIndex(refractiveIndex) {
    }

    Glass::~Glass() {
    }

    bool Glass::scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const {
        attenuation = Math::Vector3(1, 1, 1);
        double refractionRatio = record.front_face ? (1.0 / refractiveIndex) : refractiveIndex;
        Math::Vector3 unitDirection = Math::unit_vector(ray.direction);
        double cosTheta = fmin(-unitDirection.dot(record.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Math::Vector3 direction;
        if (cannotRefract || reflectance(cosTheta, refractionRatio) > Math::random_double())
            direction = Math::reflect(unitDirection, record.normal);
        else
            direction = Math::refract(unitDirection, record.normal, refractionRatio);
        scattered = Ray(record.point, direction, ray.time);
        return true;
    }

    Math::Vector3 Glass::emitted(double u, double v, const Math::Vector3 &p) const {
        return Math::Vector3(0, 0, 0);
    }

    double Glass::reflectance(double cos, double refIdx) {
        auto r0 = (1 - refIdx) / (1 + refIdx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cos), 5);
    }
}  // namespace RayTracer
