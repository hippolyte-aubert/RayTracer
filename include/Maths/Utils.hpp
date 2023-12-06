/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Utility
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <limits>
    #include <cmath>
    #include <random>
    #include <memory>
    #include "Vector3.hpp"

namespace Math {
    const double infinity = std::numeric_limits<double>::infinity();

    inline double degrees_to_radians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    inline double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }

    inline double clamp(double value, double min, double max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    inline double degreesToRadians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    inline int randomInt(int min, int max)
    {
        return static_cast<int>(random_double(min, max + 1));
    }
}

#endif /* !UTILS_HPP_ */
