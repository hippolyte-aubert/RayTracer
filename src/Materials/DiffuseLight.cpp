/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** DiffuseLight
*/

#include "DiffuseLight.hpp"

namespace RayTracer {
    DiffuseLight::DiffuseLight(std::shared_ptr<ITexture> albedo) : emit(albedo) {
    }

    DiffuseLight::DiffuseLight(Math::Vector3 color) : emit(std::make_shared<BaseTexture>(color)) {
    }

    DiffuseLight::~DiffuseLight() {
    }

    bool DiffuseLight::scatter(const Ray &r_in, const hit &rec, Math::Vector3 &attenuation, Ray &scattered) const {
        return false;
    }

    Math::Vector3 DiffuseLight::emitted(double u, double v, const Math::Vector3 &p) const {
        return emit->value(u, v, p);
    }
}  // namespace RayTracer
