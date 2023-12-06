/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Metal
*/

#ifndef METAL_HPP_
    #define METAL_HPP_

    #include "IMaterial.hpp"

namespace RayTracer {
    class Metal : public IMaterial {
        public:
            Metal(const Math::Vector3 &albedo, double fuzz);
            ~Metal();

            bool scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const override;
            Math::Vector3 emitted(double u, double v, const Math::Vector3 &p) const override;

            Math::Vector3 albedo;
            double fuzz;
        protected:
        private:
    };
}

#endif /* !METAL_HPP_ */
