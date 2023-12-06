/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Ray.hpp"
    #include "Utils.hpp"

namespace RayTracer {
    class Camera {
        public:
            // Constructors
            Camera(double aspect_ratio, double fov, Math::Vector3 lookfrom, Math::Vector3 lookat, Math::Vector3 up, double startTime = 0.0, double endTime = 0.0);
            Camera(const Camera &cpy);
            ~Camera();

            // Operators
            Camera &operator=(const Camera &other);

            // Methods
            Ray ray(double u, double v) const;

        private:
            // Attributes
            Math::Vector3 origin;
            Math::Vector3 horizontal;
            Math::Vector3 vertical;
            Math::Vector3 lower_left_corner;
            double _startTime;
            double _endTime;
    };
}

#endif /* !CAMERA_HPP_ */
