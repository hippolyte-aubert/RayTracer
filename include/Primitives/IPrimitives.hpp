/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** IPrimitives
*/

#ifndef IPRIMITIVES_HPP_
    #define IPRIMITIVES_HPP_

    #include "Ray.hpp"
    #include "IMaterial.hpp"
    #include "BoundingBoxes.hpp"
    #include "Matrix4.hpp"

namespace RayTracer {
    class IMaterial;
    struct hit {
        Math::Vector3 point;
        Math::Vector3 normal;
        std::shared_ptr<IMaterial> material;
        double t;
        double u;
        double v;
        bool front_face;

        inline void set_face_normal(const Ray &ray, const Math::Vector3 &outward_normal) {
            front_face = ray.direction.dot(outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };
    class IPrimitives {
        public:
            // Constructors
            virtual ~IPrimitives() = default;

            // Methods
            virtual bool hits(const Ray &ray, double t_min, double t_max, hit& record) const = 0;
            virtual bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const = 0;
            virtual std::string getType() const = 0;
    };
}

#endif /* !IPRIMITIVES_HPP_ */
