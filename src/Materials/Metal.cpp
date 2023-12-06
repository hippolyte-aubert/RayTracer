/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Metal
*/

#include "Metal.hpp"

namespace RayTracer {
    Metal::Metal(const Math::Vector3 &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {
    }

    Metal::~Metal() {
    }

    bool Metal::scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const {
        Math::Vector3 reflected = Math::reflect(Math::unit_vector(ray.direction), record.normal);
        scattered = Ray(record.point, reflected + fuzz * Math::random_in_unit_sphere(), ray.time);
        attenuation = albedo;
        return (scattered.direction.dot(record.normal) > 0);
    }

    Math::Vector3 Metal::emitted(double u, double v, const Math::Vector3 &p) const {
        return Math::Vector3(0, 0, 0);
    }
}  // namespace RayTracer
