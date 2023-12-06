/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace RayTracer {
    Cylinder::Cylinder() {
        type = "Cylinder";
    }

    Cylinder::Cylinder(Math::Vector3 center, double radius, double height, std::shared_ptr<IMaterial> mat) : center(center), radius(radius), height(height), material(mat) {
        type = "Cylinder";
    }

    Cylinder::~Cylinder() {
    }

    bool Cylinder::hits(const Ray &ray, double t_min, double t_max, hit &record) const {
        Math::Vector3 oc = ray.origin - center;
        double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
        double b = 2.0 * (oc.x * ray.direction.x + oc.z * ray.direction.z);
        double c = oc.x * oc.x + oc.z * oc.z - radius * radius;
        double d = b * b - 4 * a * c;
        if (d < 0)
            return false;
        double root = (-b - sqrt(d)) / (2.0 * a);
        if (root < t_min || t_max < root) {
            root = (-b + sqrt(d)) / (2.0 * a);
            if (root < t_min || t_max < root)
                return false;
        }
        auto y = ray.origin.y + root * ray.direction.y;
        if ((y < center.y) || (y > center.y + height))
            return false;
        record.t = root;
        record.point = ray.pointAt(record.t);
        record.normal = Math::Vector3((record.point.x - center.x) / radius, 0, (record.point.z - center.z) / radius);
        Math::Vector3 outward_normal = (record.point - center) / radius;
        record.set_face_normal(ray, outward_normal);
        get_cylinder_uv(outward_normal, record.u, record.v, radius);
        record.material = material;
        return true;
    }

    bool Cylinder::bounding_box(double time0, double time1, BoundingBoxes &output_box) const {
        output_box = BoundingBoxes(center - Math::Vector3(radius, height / 2, radius), center + Math::Vector3(radius, height / 2, radius));
        return true;
    }

    void Cylinder::get_cylinder_uv(const Math::Vector3 &p, double &u, double &v, double radius) {
        auto theta = std::atan2(p.x, p.z);
        auto phi = std::atan2(p.y, radius);
        u = 1 - (theta + M_PI) / (2 * M_PI);
        v = (phi + M_PI / 2) / M_PI;
    }

    std::string Cylinder::getType() const {
        return type;
    }
}  // namespace RayTracer
