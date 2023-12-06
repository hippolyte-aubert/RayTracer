/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** RotateY
*/

#ifndef ROTATEY_HPP_
    #define ROTATEY_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class RotateY : public IPrimitives {
        public:
            RotateY();
            RotateY(std::shared_ptr<IPrimitives> object, double angle);
            ~RotateY();

            bool hits(const Ray &ray, double t_min, double t_max, hit& record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

        protected:
        private:
            std::shared_ptr<IPrimitives> object;
            BoundingBoxes box;
            double angle;
            double sin_theta;
            double cos_theta;
            bool hasbox;
            std::string type;

    };
}

#endif /* !ROTATEY_HPP_ */
