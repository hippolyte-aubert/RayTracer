/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer {
    Scene::Scene() {
        type = "Scene";
    }

    Scene::Scene(std::shared_ptr<IPrimitives> object) {
        add(object);
    }

    Scene::~Scene() {
    }

    void Scene::clearScene() {
        objects.clear();
    }

    void Scene::add(std::shared_ptr<IPrimitives> object) {
        objects.push_back(object);
    }

    bool Scene::hits(const Ray &ray, double t_min, double t_max, hit &record) const {
        hit temp_record;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto &object : objects) {
            if (object->hits(ray, t_min, closest_so_far, temp_record)) {
                hit_anything = true;
                closest_so_far = temp_record.t;
                record = temp_record;
            }
        }
        return hit_anything;
    }

    bool Scene::bounding_box(double time0, double time1, BoundingBoxes &output_box) const {
        if (objects.empty())
            return false;
        BoundingBoxes temp_box;
        bool first_box = true;

        for (const auto &object : objects) {
            if (!object->bounding_box(time0, time1, temp_box))
                return false;
            output_box = first_box ? temp_box : surroundingBox(output_box, temp_box);
            first_box = false;
        }
        return true;
    }

    std::string Scene::getType() const {
        return type;
    }
}  // namespace RayTracer
