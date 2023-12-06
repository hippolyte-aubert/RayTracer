/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Box
*/

#include "Box.hpp"

namespace RayTracer {
    Box::Box() {
    }

    Box::Box(Math::Vector3 pointA, Math::Vector3 pointB, std::shared_ptr<IMaterial> mat) {
        boxMin = pointA;
        boxMax = pointB;
        type = "Box";

        sides.add(std::make_shared<Plane>("Z", pointA.x, pointB.x, pointA.y, pointB.y, pointB.z, mat));
        sides.add(std::make_shared<Plane>("Z", pointA.x, pointB.x, pointA.y, pointB.y, pointA.z, mat));
        sides.add(std::make_shared<Plane>("X", pointA.x, pointB.x, pointA.z, pointB.z, pointB.y, mat));
        sides.add(std::make_shared<Plane>("X", pointA.x, pointB.x, pointA.z, pointB.z, pointA.y, mat));
        sides.add(std::make_shared<Plane>("Y", pointA.y, pointB.y, pointA.z, pointB.z, pointB.x, mat));
        sides.add(std::make_shared<Plane>("Y", pointA.y, pointB.y, pointA.z, pointB.z, pointA.x, mat));
    }

    Box::~Box() {
    }

    bool Box::hits(const Ray &ray, double t_min, double t_max, hit &record) const {
        return sides.hits(ray, t_min, t_max, record);
    }

    bool Box::bounding_box(double time0, double time1, BoundingBoxes &output_box) const {
        output_box = BoundingBoxes(boxMin, boxMax);
        return true;
    }

    std::string Box::getType() const {
        return type;
    }
}  // namespace RayTracer
