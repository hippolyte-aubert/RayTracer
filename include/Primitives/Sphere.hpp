/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "Ray.hpp"
    #include "IPrimitives.hpp"

namespace RayTracer {
    class Sphere : public IPrimitives {
        public:
            // Constructors
            Sphere();
            Sphere(const Math::Vector3 &center, double radius, std::shared_ptr<IMaterial> mat);
            Sphere(const Sphere &other);
            ~Sphere();

            // Operators
            Sphere operator=(const Sphere &other);

            // Methods
            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

            static void get_sphere_uv(const Math::Vector3 &p, double &u, double &v);

            // Attributes
            Math::Vector3 center;
            Math::Vector3 rotation;
            double radius;
            std::shared_ptr<IMaterial> material;
        private:
            Math::Matrix4 transform;
            Math::Matrix4 inverseTransform;
            Math::Matrix4 inverseTransposeTransform;
            std::string type;
    };
}

#endif /* !SPHERE_HPP_ */
