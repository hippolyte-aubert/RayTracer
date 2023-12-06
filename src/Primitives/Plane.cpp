/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Rect
*/

#include "Plane.hpp"

namespace RayTracer {
    Plane::Plane() {
        type = "Plane";
    }

    Plane::Plane(std::string axis, double a, double b, double c, double d, double k, std::shared_ptr<IMaterial> mat) : axis(axis), a(a), b(b), c(c), d(d), k(k), material(mat) {
        type = "Plane";
    }

    Plane::~Plane() {
    }

    bool Plane::hits(const Ray& ray, double t_min, double t_max, hit& record) const {
        if (axis == "X") {
            double t = (k - ray.origin.y) / ray.direction.y;
            if (t < t_min || t > t_max)
                return false;
            double x = ray.origin.x + t * ray.direction.x;
            double z = ray.origin.z + t * ray.direction.z;
            if (x < a || x > b || z < c || z > d)
                return false;
            record.u = (x - a) / (b - a);
            record.v = (z - c) / (d - c);
            record.t = t;
            Math::Vector3 outward_normal = Math::Vector3(0, 1, 0);
            record.set_face_normal(ray, outward_normal);
            record.material = material;
            record.point = ray.pointAt(t);
            return true;
        }
        if (axis == "Y") {
            double t = (k - ray.origin.x) / ray.direction.x;
            if (t < t_min || t > t_max)
                return false;
            double y = ray.origin.y + t * ray.direction.y;
            double z = ray.origin.z + t * ray.direction.z;
            if (y < a || y > b || z < c || z > d)
                return false;
            record.u = (y - a) / (b - a);
            record.v = (z - c) / (d - c);
            record.t = t;
            Math::Vector3 outward_normal = Math::Vector3(1, 0, 0);
            record.set_face_normal(ray, outward_normal);
            record.material = material;
            record.point = ray.pointAt(t);
            return true;
        }
        if (axis == "Z") {
            double t = (k - ray.origin.z) / ray.direction.z;
            if (t < t_min || t > t_max)
                return false;
            double x = ray.origin.x + t * ray.direction.x;
            double y = ray.origin.y + t * ray.direction.y;
            if (x < a || x > b || y < c || y > d)
                return false;
            record.u = (x - a) / (b - a);
            record.v = (y - c) / (d - c);
            record.t = t;
            Math::Vector3 outward_normal = Math::Vector3(0, 0, 1);
            record.set_face_normal(ray, outward_normal);
            record.material = material;
            record.point = ray.pointAt(t);
            return true;
        }
        return false;
    }

    bool Plane::bounding_box(double t0, double t1, BoundingBoxes& output_box) const {
        if (axis == "X") {
            output_box = BoundingBoxes(Math::Vector3(a, k - 0.0001, c), Math::Vector3(b, k + 0.0001, d));
            return true;
        } else if (axis == "Y") {
            output_box = BoundingBoxes(Math::Vector3(k - 0.0001, a, c), Math::Vector3(k + 0.0001, b, d));
            return true;
        } else if (axis == "Z") {
            output_box = BoundingBoxes(Math::Vector3(a, c, k - 0.0001), Math::Vector3(b, d, k + 0.0001));
            return true;
        } else {
            return false;
        }
    }

    std::string Plane::getType() const {
        return type;
    }
}  // namespace RayTracer
