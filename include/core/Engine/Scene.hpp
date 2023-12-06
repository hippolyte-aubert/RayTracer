/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_

    #include "IPrimitives.hpp"
    #include <vector>
    #include <memory>

namespace RayTracer {
    class Scene : public IPrimitives {
        public:
            Scene();
            Scene(std::shared_ptr<IPrimitives> object);
            ~Scene();

            void clearScene();
            void add(std::shared_ptr<IPrimitives> object);

            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

            std::vector<std::shared_ptr<IPrimitives>> objects;
        private:
            std::string type;
    };
}

#endif /* !SCENE_HPP_ */
