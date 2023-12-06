/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Matrix4
*/

#include "Matrix4.hpp"

namespace Math {
    Matrix4::Matrix4() {
        _matrix = {{{1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}}};
    }

    Matrix4::Matrix4(const Matrix4 &other) : _matrix(other._matrix) {
    }

    Matrix4::~Matrix4() {
    }

    Matrix4 Matrix4::operator=(const Matrix4 &other) {
        if (this != &other) {
            _matrix = other._matrix;
        }
        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4 &other) const {
        Matrix4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result._matrix[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result._matrix[i][j] += this->_matrix[i][k] * other._matrix[k][j];
                }
            }
        }
        return result;
    }

    Matrix4 Matrix4::identity() {
        return Matrix4();
    }

    Matrix4 Matrix4::translate(const Vector3 &vec) {
        Matrix4 result;

        result._matrix[0][3] = vec.x;
        result._matrix[1][3] = vec.y;
        result._matrix[2][3] = vec.z;
        return result;
    }

    Matrix4 Matrix4::scale(double sx, double sy, double sz) {
        Matrix4 result;

        result._matrix[0][0] = sx;
        result._matrix[1][1] = sy;
        result._matrix[2][2] = sz;
        return result;
    }

    Matrix4 Matrix4::rotateX(double angle) {
        Matrix4 result;
        double rad = degreesToRadians(angle);

        result._matrix[1][1] = cos(rad);
        result._matrix[1][2] = -sin(rad);
        result._matrix[2][1] = sin(rad);
        result._matrix[2][2] = cos(rad);
        return result;
    }

    Matrix4 Matrix4::rotateY(double angle) {
        Matrix4 result;
        double rad = degreesToRadians(angle);

        result._matrix[0][0] = cos(rad);
        result._matrix[0][2] = sin(rad);
        result._matrix[2][0] = -sin(rad);
        result._matrix[2][2] = cos(rad);
        return result;
    }

    Matrix4 Matrix4::rotateZ(double angle) {
        Matrix4 result;
        double rad = degreesToRadians(angle);

        result._matrix[0][0] = cos(rad);
        result._matrix[0][1] = -sin(rad);
        result._matrix[1][0] = sin(rad);
        result._matrix[1][1] = cos(rad);
        return result;
    }

    Matrix4 Matrix4::transpose() {
        Matrix4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result._matrix[i][j] = _matrix[j][i];
            }
        }
        return result;
    }

    Matrix4 Matrix4::inverse() {
        Matrix4 inverse;

        inverse._matrix[0][0] = _matrix[1][1] * _matrix[2][2] * _matrix[3][3] -
                                _matrix[1][1] * _matrix[2][3] * _matrix[3][2] -
                                _matrix[2][1] * _matrix[1][2] * _matrix[3][3] +
                                _matrix[2][1] * _matrix[1][3] * _matrix[3][2] +
                                _matrix[3][1] * _matrix[1][2] * _matrix[2][3] -
                                _matrix[3][1] * _matrix[1][3] * _matrix[2][2];

        inverse._matrix[1][0] = -_matrix[1][0] * _matrix[2][2] * _matrix[3][3] +
                                _matrix[1][0] * _matrix[2][3] * _matrix[3][2] +
                                _matrix[2][0] * _matrix[1][2] * _matrix[3][3] -
                                _matrix[2][0] * _matrix[1][3] * _matrix[3][2] -
                                _matrix[3][0] * _matrix[1][2] * _matrix[2][3] +
                                _matrix[3][0] * _matrix[1][3] * _matrix[2][2];

        inverse._matrix[2][0] = _matrix[1][0] * _matrix[2][1] * _matrix[3][3] -
                                _matrix[1][0] * _matrix[2][3] * _matrix[3][1] -
                                _matrix[2][0] * _matrix[1][1] * _matrix[3][3] +
                                _matrix[2][0] * _matrix[1][3] * _matrix[3][1] +
                                _matrix[3][0] * _matrix[1][1] * _matrix[2][3] -
                                _matrix[3][0] * _matrix[1][3] * _matrix[2][1];

        inverse._matrix[3][0] = -_matrix[1][0] * _matrix[2][1] * _matrix[3][2] +
                                _matrix[1][0] * _matrix[2][2] * _matrix[3][1] +
                                _matrix[2][0] * _matrix[1][1] * _matrix[3][2] -
                                _matrix[2][0] * _matrix[1][2] * _matrix[3][1] -
                                _matrix[3][0] * _matrix[1][1] * _matrix[2][2] +
                                _matrix[3][0] * _matrix[1][2] * _matrix[2][1];

        inverse._matrix[0][1] = -_matrix[0][1] * _matrix[2][2] * _matrix[3][3] +
                                _matrix[0][1] * _matrix[2][3] * _matrix[3][2] +
                                _matrix[2][1] * _matrix[0][2] * _matrix[3][3] -
                                _matrix[2][1] * _matrix[0][3] * _matrix[3][2] -
                                _matrix[3][1] * _matrix[0][2] * _matrix[2][3] +
                                _matrix[3][1] * _matrix[0][3] * _matrix[2][2];

        inverse._matrix[1][1] = _matrix[0][0] * _matrix[2][2] * _matrix[3][3] -
                                _matrix[0][0] * _matrix[2][3] * _matrix[3][2] -
                                _matrix[2][0] * _matrix[0][2] * _matrix[3][3] +
                                _matrix[2][0] * _matrix[0][3] * _matrix[3][2] +
                                _matrix[3][0] * _matrix[0][2] * _matrix[2][3] -
                                _matrix[3][0] * _matrix[0][3] * _matrix[2][2];

        inverse._matrix[2][1] = -_matrix[0][0] * _matrix[2][1] * _matrix[3][3] +
                                _matrix[0][0] * _matrix[2][3] * _matrix[3][1] +
                                _matrix[2][0] * _matrix[0][1] * _matrix[3][3] -
                                _matrix[2][0] * _matrix[0][3] * _matrix[3][1] -
                                _matrix[3][0] * _matrix[0][1] * _matrix[2][3] +
                                _matrix[3][0] * _matrix[0][3] * _matrix[2][1];

        inverse._matrix[3][1] = _matrix[0][0] * _matrix[2][1] * _matrix[3][2] -
                                _matrix[0][0] * _matrix[2][2] * _matrix[3][1] -
                                _matrix[2][0] * _matrix[0][1] * _matrix[3][2] +
                                _matrix[2][0] * _matrix[0][2] * _matrix[3][1] +
                                _matrix[3][0] * _matrix[0][1] * _matrix[2][2] -
                                _matrix[3][0] * _matrix[0][2] * _matrix[2][1];

        inverse._matrix[0][2] = _matrix[0][1] * _matrix[1][2] * _matrix[3][3] -
                                _matrix[0][1] * _matrix[1][3] * _matrix[3][2] -
                                _matrix[1][1] * _matrix[0][2] * _matrix[3][3] +
                                _matrix[1][1] * _matrix[0][3] * _matrix[3][2] +
                                _matrix[3][1] * _matrix[0][2] * _matrix[1][3] -
                                _matrix[3][1] * _matrix[0][3] * _matrix[1][2];

        inverse._matrix[1][2] = -_matrix[0][0] * _matrix[1][2] * _matrix[3][3] +
                                _matrix[0][0] * _matrix[1][3] * _matrix[3][2] +
                                _matrix[1][0] * _matrix[0][2] * _matrix[3][3] -
                                _matrix[1][0] * _matrix[0][3] * _matrix[3][2] -
                                _matrix[3][0] * _matrix[0][2] * _matrix[1][3] +
                                _matrix[3][0] * _matrix[0][3] * _matrix[1][2];

        inverse._matrix[2][2] = _matrix[0][0] * _matrix[1][1] * _matrix[3][3] -
                                _matrix[0][0] * _matrix[1][3] * _matrix[3][1] -
                                _matrix[1][0] * _matrix[0][1] * _matrix[3][3] +
                                _matrix[1][0] * _matrix[0][3] * _matrix[3][1] +
                                _matrix[3][0] * _matrix[0][1] * _matrix[1][3] -
                                _matrix[3][0] * _matrix[0][3] * _matrix[1][1];

        inverse._matrix[3][2] = -_matrix[0][0] * _matrix[1][1] * _matrix[3][2] +
                                _matrix[0][0] * _matrix[1][2] * _matrix[3][1] +
                                _matrix[1][0] * _matrix[0][1] * _matrix[3][2] -
                                _matrix[1][0] * _matrix[0][2] * _matrix[3][1] -
                                _matrix[3][0] * _matrix[0][1] * _matrix[1][2] +
                                _matrix[3][0] * _matrix[0][2] * _matrix[1][1];

        inverse._matrix[0][3] = -_matrix[0][1] * _matrix[1][2] * _matrix[2][3] +
                                _matrix[0][1] * _matrix[1][3] * _matrix[2][2] +
                                _matrix[1][1] * _matrix[0][2] * _matrix[2][3] -
                                _matrix[1][1] * _matrix[0][3] * _matrix[2][2] -
                                _matrix[2][1] * _matrix[0][2] * _matrix[1][3] +
                                _matrix[2][1] * _matrix[0][3] * _matrix[1][2];

        inverse._matrix[1][3] = _matrix[0][0] * _matrix[1][2] * _matrix[2][3] -
                                _matrix[0][0] * _matrix[1][3] * _matrix[2][2] -
                                _matrix[1][0] * _matrix[0][2] * _matrix[2][3] +
                                _matrix[1][0] * _matrix[0][3] * _matrix[2][2] +
                                _matrix[2][0] * _matrix[0][2] * _matrix[1][3] -
                                _matrix[2][0] * _matrix[0][3] * _matrix[1][2];

        inverse._matrix[2][3] = -_matrix[0][0] * _matrix[1][1] * _matrix[2][3] +
                                _matrix[0][0] * _matrix[1][3] * _matrix[2][1] +
                                _matrix[1][0] * _matrix[0][1] * _matrix[2][3] -
                                _matrix[1][0] * _matrix[0][3] * _matrix[2][1] -
                                _matrix[2][0] * _matrix[0][1] * _matrix[1][3] +
                                _matrix[2][0] * _matrix[0][3] * _matrix[1][1];

        inverse._matrix[3][3] = _matrix[0][0] * _matrix[1][1] * _matrix[2][2] -
                                _matrix[0][0] * _matrix[1][2] * _matrix[2][1] -
                                _matrix[1][0] * _matrix[0][1] * _matrix[2][2] +
                                _matrix[1][0] * _matrix[0][2] * _matrix[2][1] +
                                _matrix[2][0] * _matrix[0][1] * _matrix[1][2] -
                                _matrix[2][0] * _matrix[0][2] * _matrix[1][1];

        float determinant = _matrix[0][0] * inverse._matrix[0][0] +
                            _matrix[0][1] * inverse._matrix[1][0] + _matrix[0][2] * inverse._matrix[2][0] + _matrix[0][3] * inverse._matrix[3][0];

        if (determinant == 0)
            return Matrix4();
        determinant = 1.0f / determinant;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                inverse._matrix[i][j] *= determinant;
        return inverse;
    }

    std::array<std::array<double, 4>, 4> Matrix4::getMatrix() const {
        return _matrix;
    }
}  // namespace Math
