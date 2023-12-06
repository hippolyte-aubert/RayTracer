/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** RotateX
*/

#include "RotateX.hpp"

namespace RayTracer {
    RotateX::RotateX() {
        type = "RotateX";
    }

    RotateX::RotateX(std::shared_ptr<IPrimitives> object, double angle) : object(object) {
        double rad = Math::degreesToRadians(angle);

        this->sin_theta = sin(rad);
        this->cos_theta = cos(rad);
        this->hasbox = this->object->bounding_box(0, 1, this->box);

        Math::Vector3 min(Math::infinity, Math::infinity, Math::infinity);
        Math::Vector3 max(-Math::infinity, -Math::infinity, -Math::infinity);

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    double x = i * this->box.max().x + (1 - i) * this->box.min().x;
                    double y = j * this->box.max().y + (1 - j) * this->box.min().y;
                    double z = k * this->box.max().z + (1 - k) * this->box.min().z;

                    double newY = this->cos_theta * y - this->sin_theta * z;
                    double newZ = this->sin_theta * y + this->cos_theta * z;

                    Math::Vector3 tester(x, newY, newZ);
                    for (int l = 0; l < 3; l++) {
                        min[l] = fmin(min[l], tester[l]);
                        max[l] = fmax(max[l], tester[l]);
                    }
                }
        this->box = BoundingBoxes(min, max);
        this->type = this->object->getType() + " rotated on X axis";
    }

    RotateX::~RotateX() {
    }

    bool RotateX::hits(const Ray& ray, double t_min, double t_max, hit& record) const {
        Math::Vector3 origin = ray.origin;
        Math::Vector3 direction = ray.direction;

        origin.y = this->cos_theta * ray.origin.y - this->sin_theta * ray.origin.z;
        origin.z = this->sin_theta * ray.origin.y + this->cos_theta * ray.origin.z;

        direction.y = this->cos_theta * ray.direction.y - this->sin_theta * ray.direction.z;
        direction.z = this->sin_theta * ray.direction.y + this->cos_theta * ray.direction.z;

        Ray rotated_ray(origin, direction, ray.time);

        if (!this->object->hits(rotated_ray, t_min, t_max, record))
            return false;

        Math::Vector3 point = record.point;
        Math::Vector3 normal = record.normal;

        point.y = this->cos_theta * record.point.y + this->sin_theta * record.point.z;
        point.z = -this->sin_theta * record.point.y + this->cos_theta * record.point.z;

        record.point = point;
        record.set_face_normal(rotated_ray, normal);

        return true;
    }

    bool RotateX::bounding_box(double time0, double time1, BoundingBoxes& output_box) const {
        output_box = box;
        return hasbox;
    }

    std::string RotateX::getType() const {
        return type;
    }
}
