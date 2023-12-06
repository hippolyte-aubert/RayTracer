/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "Vector3.hpp"

namespace RayTracer {
    class Ray {
        public:
            // Constructors
            Ray();
            Ray(const Math::Vector3 &origin, const Math::Vector3 &direction, double time = 0.0);
            Ray(const Ray &other);
            Ray(const Ray &&other) noexcept;
            ~Ray();

            // Operators
            Ray operator=(const Ray &other);
            Ray operator=(const Ray &&other) noexcept;

            // Methods
            Math::Vector3 pointAt(double t) const;

            // Attributes
            Math::Vector3 origin;
            Math::Vector3 direction;
            double time;
    };
}

#endif /* !RAY_HPP_ */
