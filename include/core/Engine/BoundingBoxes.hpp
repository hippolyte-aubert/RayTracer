/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** BoundingBoxes
*/

#ifndef BOUNDINGBOXES_HPP_
    #define BOUNDINGBOXES_HPP_

    #include "Vector3.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    class BoundingBoxes {
        public:
            BoundingBoxes();
            BoundingBoxes(const Math::Vector3 &min, const Math::Vector3 &max);
            ~BoundingBoxes();

            Math::Vector3 min() const;
            Math::Vector3 max() const;

            bool hit(const Ray &ray, double t_min, double t_max) const;

        private:
            Math::Vector3 minimum;
            Math::Vector3 maximum;
    };
    BoundingBoxes surroundingBox(BoundingBoxes box1, BoundingBoxes box2);
}

#endif /* !BOUNDINGBOXES_HPP_ */
