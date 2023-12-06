/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace RayTracer {
    Sphere::Sphere() : center(Math::Vector3()), rotation(Math::Vector3()), radius(0) {
        type = "Sphere";
    }

    Sphere::Sphere(const Math::Vector3 &center, double radius, std::shared_ptr<IMaterial> mat) : center(center), radius(radius), material(mat) {
        type = "Sphere";
        // Math::Matrix4 translation = Math::Matrix4::translate(center);
        // Math::Matrix4 rotationX = Math::Matrix4::rotateX(rotation.x);
        // Math::Matrix4 rotationY = Math::Matrix4::rotateY(rotation.y);
        // Math::Matrix4 rotationZ = Math::Matrix4::rotateZ(rotation.z);

        // transform = translation * rotationX * rotationY * rotationZ;
        // inverseTransform = transform.inverse();
        // inverseTransposeTransform = inverseTransform.transpose();
    }

    Sphere::Sphere(const Sphere &other) : center(other.center), rotation(other.rotation), radius(other.radius) {
    }

    Sphere::~Sphere() {
    }

    Sphere Sphere::operator=(const Sphere &other) {
        if (this != &other) {
            center = other.center;
            rotation = other.rotation;
            radius = other.radius;
        }
        return *this;
    }

    bool Sphere::hits(const RayTracer::Ray &ray, double t_min, double t_max, hit &record) const {
        Math::Vector3 oc = ray.origin - center;
        double a = ray.direction.length_squared();
        double b = ray.direction.dot(oc);
        double c = oc.length_squared() - radius * radius;
        double d = b * b - a * c;
        if (d < 0)
            return false;
        auto square_root_d = std::sqrt(d);
        auto root = (-b - square_root_d) / a;
        if (root < t_min || t_max < root) {
            root = (-b + square_root_d) / a;
            if (root < t_min || t_max < root)
                return false;
        }
        record.t = root;
        record.point = ray.pointAt(record.t);
        record.normal = ((record.point - center) / radius);
        Math::Vector3 outward_normal = (record.point - center) / radius;
        record.set_face_normal(ray, outward_normal);
        get_sphere_uv(outward_normal, record.u, record.v);
        record.material = material;
        return true;
    }

    bool Sphere::bounding_box(double time0, double time1, BoundingBoxes &output_box) const {
        output_box = BoundingBoxes(
            center - Math::Vector3(radius, radius, radius),
            center + Math::Vector3(radius, radius, radius));
        return true;
    }

    void Sphere::get_sphere_uv(const Math::Vector3 &p, double &u, double &v) {
        auto theta = std::acos(-p.y);
        auto phi = std::atan2(-p.z, p.x) + M_PI;
        u = phi / (2 * M_PI);
        v = theta / M_PI;
    }

    std::string Sphere::getType() const {
        return type;
    }
}  // namespace RayTracer
