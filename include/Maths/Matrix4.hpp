/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Matrix4
*/

#ifndef MATRIX4_HPP_
    #define MATRIX4_HPP_

    #include <array>
    #include <cmath>
    #include "Vector3.hpp"
    #include "Utils.hpp"

namespace Math {
    class Vector3;
    class Matrix4 {
        public:
            // Constructors
            Matrix4();
            Matrix4(const Matrix4 &other);
            ~Matrix4();

            // Operators
            Matrix4 operator=(const Matrix4 &other);
            Matrix4 operator*(const Matrix4 &other) const;

            // Methods
            static Matrix4 identity();
            static Matrix4 translate(const Vector3 &vec);
            static Matrix4 scale(double sx, double sy, double sz);
            static Matrix4 rotateX(double angle);
            static Matrix4 rotateY(double angle);
            static Matrix4 rotateZ(double angle);
            Matrix4 transpose();
            Matrix4 inverse();

            // Getter
            std::array<std::array<double, 4>, 4> getMatrix() const;
        protected:
        private:
            std::array<std::array<double, 4>, 4> _matrix;
    };
}

#endif /* !MATRIX4_HPP_ */
