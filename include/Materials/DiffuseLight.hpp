/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** DiffuseLight
*/

#ifndef DIFFUSELIGHT_HPP_
    #define DIFFUSELIGHT_HPP_

    #include "Vector3.hpp"
    #include "ITexture.hpp"
    #include "IMaterial.hpp"
    #include "BaseTexture.hpp"

namespace RayTracer {
    class DiffuseLight : public IMaterial {
        public:
            DiffuseLight(std::shared_ptr<ITexture> albedo);
            DiffuseLight(Math::Vector3 color);
            ~DiffuseLight();

            bool scatter (const Ray &r_in, const hit &rec, Math::Vector3 &attenuation, Ray &scattered) const override;
            Math::Vector3 emitted(double u, double v, const Math::Vector3 &p) const override;

            std::shared_ptr<ITexture> emit;

    };
}

#endif /* !DIFFUSELIGHT_HPP_ */
