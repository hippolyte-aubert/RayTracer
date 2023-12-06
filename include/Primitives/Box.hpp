/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Box
*/

#ifndef BOX_HPP_
    #define BOX_HPP_

    #include "IPrimitives.hpp"
    #include "Scene.hpp"
    #include "Plane.hpp"

namespace RayTracer {
    class Box : public IPrimitives {
        public:
            Box();
            Box(Math::Vector3 pointA, Math::Vector3 pointB, std::shared_ptr<IMaterial> mat);
            ~Box();

            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

        protected:
        private:
            std::string type;
            Math::Vector3 boxMin;
            Math::Vector3 boxMax;
            Scene sides;
    };
}

#endif /* !BOX_HPP_ */
