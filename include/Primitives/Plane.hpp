/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Rect
*/

#ifndef PLANE_HPP_
    #define PLANE_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class Plane : public IPrimitives {
        public:
            Plane();
            Plane(std::string axis, double a, double b, double c, double d, double k, std::shared_ptr<IMaterial> mat);
            ~Plane();

            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

            // Attributes
            double a, b, c, d, k;
            std::string axis;
            std::shared_ptr<IMaterial> material;
        private:
            std::string type;
    };
}

#endif /* !PLANE_HPP_ */
