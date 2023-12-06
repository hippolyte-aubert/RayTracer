/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Glass
*/

#ifndef GLASS_HPP_
    #define GLASS_HPP_

    #include "IMaterial.hpp"

namespace RayTracer {
    class Glass : public IMaterial {
        public:
            Glass(double refractiveIndex);
            ~Glass();

            bool scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const override;
            Math::Vector3 emitted(double u, double v, const Math::Vector3 &p) const override;

            double refractiveIndex;
        protected:
        private:
            static double reflectance(double cos, double refIdx);
    };
}

#endif /* !GLASS_HPP_ */
