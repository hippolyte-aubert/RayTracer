/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
    #define CYLINDER_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class Cylinder : public IPrimitives {
        public:
            Cylinder();
            Cylinder(Math::Vector3 center, double radius, double height, std::shared_ptr<IMaterial> mat);
            ~Cylinder();

            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

            static void get_cylinder_uv(const Math::Vector3 &p, double &u, double &v, double radius);
            // Attributes
            Math::Vector3 center;
            double radius;
            double height;
            std::shared_ptr<IMaterial> material;

        protected:
        private:
            std::string type;
    };
}

#endif /* !CYLINDER_HPP_ */
