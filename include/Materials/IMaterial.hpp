/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
    #define IMATERIAL_HPP_

    #include "Utils.hpp"
    #include "IPrimitives.hpp"

namespace RayTracer {
    struct hit;
    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual bool scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const = 0;
            virtual Math::Vector3 emitted(double u, double v, const Math::Vector3 &p) const = 0;

        protected:
        private:
    };
}

#endif /* !IMATERIAL_HPP_ */
