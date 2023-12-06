/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Translate
*/

#ifndef TRANSLATE_HPP_
    #define TRANSLATE_HPP_

    #include "IPrimitives.hpp"

namespace RayTracer {
    class Translate : public IPrimitives {
        public:
            Translate();
            Translate(std::shared_ptr<IPrimitives> prim, Math::Vector3 offset);
            ~Translate();

            bool hits(const Ray &ray, double t_min, double t_max, hit &record) const override;
            bool bounding_box(double time0, double time1, BoundingBoxes &output_box) const override;
            std::string getType() const override;

        protected:
        private:
            std::shared_ptr<IPrimitives> prim;
            Math::Vector3 offset;
            std::string type;
    };
}

#endif /* !TRANSLATE_HPP_ */
