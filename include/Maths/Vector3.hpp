/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Vector3
*/

#ifndef Vector3_HPP_
    #define Vector3_HPP_

    #include <iostream>
    #include <cmath>
    #include "Matrix4.hpp"

namespace Math {
    class Matrix4;
    class Vector3 {
        public:
            // Constructors
            Vector3();
            Vector3(double x, double y, double z);
            Vector3(const Vector3 &other);
            Vector3(const Vector3 &&other) noexcept;
            ~Vector3();

            // Operators
            Vector3 operator=(const Vector3 &other);
            Vector3 operator=(const Vector3 &&other) noexcept;
            Vector3 operator+(const Vector3 &other) const;
            Vector3 operator+=(const Vector3 &other);
            Vector3 operator-(const Vector3 &other) const;
            Vector3 operator-=(const Vector3 &other);
            Vector3 operator*(const Vector3 &other) const;
            Vector3 operator*=(const Vector3 &other);
            Vector3 operator/(const Vector3 &other) const;
            Vector3 operator/=(const Vector3 &other);

            Vector3 operator*(double scalar) const;
            Vector3 operator*=(double scalar);
            Vector3 operator/(double scalar) const;
            Vector3 operator/=(double scalar);

            Vector3 operator*(const Matrix4 &matrix) const;

            double operator[](int i) const;
            double &operator[](int i);

            // Methods
            double length() const;
            double length_squared() const;
            double dot(const Vector3 &other) const;
            Vector3 cross(const Vector3 &other) const;
            static Vector3 random();
            static Vector3 random(double min, double max);
            bool near_zero() const;

            // Attributes
            double x;
            double y;
            double z;
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector3 &vector) {
        os << "x: " << vector.x << " y: " << vector.y << " z: " << vector.z;
        return os;
    }

    inline Vector3 operator*(double scalar, const Vector3 &vector) {
        return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
    }

    inline Vector3 operator-(const Vector3 &vector) {
        return Vector3(-vector.x, -vector.y, -vector.z);
    }

    inline Vector3 operator-(const Vector3 &vector, double scalar) {
        return Vector3(vector.x - scalar, vector.y - scalar, vector.z - scalar);
    }

    Vector3 unit_vector(Vector3 vector);
    Vector3 random_in_unit_sphere();
    Vector3 random_unit_vector();
    Vector3 random_in_hemisphere(const Vector3 &normal);
    Vector3 reflect(const Vector3 &vector, const Vector3 &normal);
    Vector3 refract(const Vector3 &vector, const Vector3 &normal, double etai_over_etat);
}

#endif /* !Vector3_HPP_ */
