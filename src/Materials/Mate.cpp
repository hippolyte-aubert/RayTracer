/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Mate
*/

#include "Mate.hpp"

namespace RayTracer {
    Mate::Mate(const Math::Vector3 &albedo) : albedo(std::make_shared<BaseTexture>(albedo)) {
    }

    Mate::Mate(const std::shared_ptr<ITexture> &texture) : albedo(texture) {
    }

    Mate::~Mate() {
    }

    bool Mate::scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const {
        auto scatter_direction = record.normal + Math::random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = record.normal;
        scattered = Ray(record.point, scatter_direction, ray.time);
        attenuation = albedo->value(record.u, record.v, record.point);
        return true;
    }

    Math::Vector3 Mate::emitted(double u, double v, const Math::Vector3 &p) const {
        return Math::Vector3(0, 0, 0);
    }
}  // namespace RayTracer
