/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** RotateX
*/

#ifndef ROTATEX_HPP_
    #define ROTATEX_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class RotateX : public IPrimitives{
        public:
            RotateX();
            RotateX(std::shared_ptr<IPrimitives> object, double angle);
            ~RotateX();

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

#endif /* !ROTATEX_HPP_ */
