/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Cone
*/

#ifndef CONE_HPP_
    #define CONE_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class Cone : public IPrimitives {
        public:
            Cone();
            Cone(const Math::Vector3 &center, double radius, double height, std::shared_ptr<IMaterial> mat);
            ~Cone();

            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

            static void get_cone_uv(const Math::Vector3 &p, double &u, double &v);
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

#endif /* !CONE_HPP_ */