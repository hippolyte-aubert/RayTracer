/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Ray
*/

#include "Ray.hpp"

namespace RayTracer {

    Ray::Ray() : origin(Math::Vector3()), direction(Math::Vector3()), time(0.0) {
    }

    Ray::Ray(const Math::Vector3 &origin, const Math::Vector3 &direction, double time) : origin(origin), direction(direction), time(time)
    {
    }

    Ray::Ray(const Ray &other) : origin(other.origin), direction(other.direction), time(other.time){
    }

    Ray::Ray(const Ray &&other) noexcept : origin(std::move(other.origin)), direction(std::move(other.direction)), time(std::move(other.time)) {
    }

    Ray::~Ray() {
    }

    Ray Ray::operator=(const Ray &other) {
        if (this != &other) {
            origin = other.origin;
            direction = other.direction;
        }
        return *this;
    }

    Ray Ray::operator=(const Ray &&other) noexcept {
        if (this != &other) {
            origin = std::move(other.origin);
            direction = std::move(other.direction);
        }
        return *this;
    }

    Math::Vector3 Ray::pointAt(double t) const {
        return origin + t * direction;
    }
}  // namespace RayTracer
