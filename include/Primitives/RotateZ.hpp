/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** RotateZ
*/

#ifndef ROTATEZ_HPP_
    #define ROTATEZ_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class RotateZ : public IPrimitives {
        public:
            RotateZ();
            RotateZ(std::shared_ptr<IPrimitives> prim, double angle);
            ~RotateZ();

            bool hits(const Ray &ray, double t_min, double t_max, hit &record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

        protected:
        private:
            std::shared_ptr<IPrimitives> object;
            double angle;
            double sin_theta;
            double cos_theta;
            bool hasbox;
            BoundingBoxes box;
            std::string type;
    };
}

#endif /* !ROTATEZ_HPP_ */
