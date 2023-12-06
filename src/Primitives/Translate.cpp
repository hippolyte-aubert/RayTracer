/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Translate
*/

#include "Translate.hpp"

namespace RayTracer {
    Translate::Translate()
    {
        type = "Translate";
    }

    Translate::Translate(std::shared_ptr<IPrimitives> prim, Math::Vector3 offset) : prim(prim), offset(offset)
    {
        type = prim->getType() + "Translated";
    }

    Translate::~Translate()
    {
    }

    bool Translate::hits(const Ray &ray, double t_min, double t_max, hit &record) const
    {
        Ray moved_ray(ray.origin - offset, ray.direction, ray.time);
        if (!prim->hits(moved_ray, t_min, t_max, record))
            return false;
        record.point += offset;
        record.set_face_normal(moved_ray, record.normal);
        return true;
    }

    bool Translate::bounding_box(double time0, double time1, BoundingBoxes &output_box) const
    {
        if (!prim->bounding_box(time0, time1, output_box))
            return false;
        output_box = BoundingBoxes(output_box.min() + offset, output_box.max() + offset);
        return true;
    }

    std::string Translate::getType() const
    {
        return type;
    }
}
