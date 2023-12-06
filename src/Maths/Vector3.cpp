/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Vector3
*/

#include "Vector3.hpp"

#include "Utils.hpp"

namespace Math {
    Vector3::Vector3() : x(0), y(0), z(0) {
    }

    Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {
    }

    Vector3::Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {
    }

    Vector3::Vector3(const Vector3 &&other) noexcept : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {
    }

    Vector3::~Vector3() {
    }

    Vector3 Vector3::operator=(const Vector3 &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Vector3 Vector3::operator=(const Vector3 &&other) noexcept {
        if (this != &other) {
            x = std::move(other.x);
            y = std::move(other.y);
            z = std::move(other.z);
        }
        return *this;
    }

    Vector3 Vector3::operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator+=(const Vector3 &other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator-=(const Vector3 &other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vector3 Vector3::operator*(const Vector3 &other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 Vector3::operator*=(const Vector3 &other) {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }

    Vector3 Vector3::operator/(const Vector3 &other) const {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    Vector3 Vector3::operator/=(const Vector3 &other) {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        return *this;
    }

    Vector3 Vector3::operator*(double scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 Vector3::operator*=(double scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }

    Vector3 Vector3::operator/(double scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    Vector3 Vector3::operator/=(double scalar) {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }

    Vector3 Vector3::operator*(const Matrix4 &mat) const {
        std::array<std::array<double, 4>, 4> matrix = mat.getMatrix();
        return Vector3(x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + matrix[3][0],
                    x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + matrix[3][1],
                    x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + matrix[3][2]);
    }

    double Vector3::operator[](int index) const {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else
            return z;
    }

    double &Vector3::operator[](int index) {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else
            return z;
    }

    double Vector3::length() const {
        return sqrt(x * x + y * y + z * z);
    }

    double Vector3::length_squared() const {
        return (x * x + y * y + z * z);
    }

    double Vector3::dot(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::cross(const Vector3 &other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    Vector3 Vector3::random() {
        return Vector3(random_double(), random_double(), random_double());
    }

    Vector3 Vector3::random(double min, double max) {
        return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool Vector3::near_zero() const {
        const double s = 1e-8;
        return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
    }

    Vector3 unit_vector(Vector3 v) {
        return v / v.length();
    }

    Vector3 random_in_unit_sphere() {
        while (true) {
            Vector3 p = Vector3::random(-1, 1);
            if (p.length_squared() >= 1)
                continue;
            return p;
        }
    }

    Vector3 random_unit_vector() {
        return unit_vector(random_in_unit_sphere());
    }

    Vector3 random_in_hemisphere(const Vector3 &normal) {
        Vector3 in_unit_sphere = random_in_unit_sphere();
        if (in_unit_sphere.dot(normal) > 0.0)
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    Vector3 reflect(const Vector3 &v, const Vector3 &n) {
        return v - 2 * v.dot(n) * n;
    }

    Vector3 refract(const Vector3 &uv, const Vector3 &n, double etai_over_etat) {
        auto cos_theta = std::fmin(-uv.dot(n), 1.0);
        Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
        Vector3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }
}  // namespace Math
