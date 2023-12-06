/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Camera
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera(double aspect_ratio, double fov, Math::Vector3 lookFrom, Math::Vector3 lookAt, Math::Vector3 up, double startTime, double endTime) {
        auto theta = Math::degreesToRadians(fov);
        auto h = std::tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        auto w = Math::unit_vector(lookFrom - lookAt);
        auto u = Math::unit_vector(up.cross(w));
        auto v = w.cross(u);

        origin = lookFrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;

        _startTime = startTime;
        _endTime = endTime;
    }

    Camera::Camera(const Camera &cpy) : origin(cpy.origin), horizontal(cpy.horizontal), vertical(cpy.vertical), lower_left_corner(cpy.lower_left_corner) {
    }

    Camera::~Camera() {
    }

    Camera &Camera::operator=(const Camera &other) {
        if (this != &other) {
            origin = other.origin;
            horizontal = other.horizontal;
            vertical = other.vertical;
            lower_left_corner = other.lower_left_corner;
        }
        return *this;
    }

    Ray Camera::ray(double u, double v) const {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin, Math::random_double(_startTime, _endTime));
    }
}
