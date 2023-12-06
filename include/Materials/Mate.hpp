/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-theo.faupin
** File description:
** Mate
*/

#ifndef MATE_HPP_
    #define MATE_HPP_

    #include "IMaterial.hpp"
    #include "ITexture.hpp"
    #include "BaseTexture.hpp"

namespace RayTracer {
    class Mate : public IMaterial{
        public:
            Mate(const Math::Vector3 &albedo);
            Mate(const std::shared_ptr<ITexture> &texture);
            ~Mate();

            bool scatter(const Ray &ray, const hit &record, Math::Vector3 &attenuation, Ray &scattered) const override;
            Math::Vector3 emitted(double u, double v, const Math::Vector3 &p) const override;
            std::shared_ptr<ITexture> albedo;
        protected:
        private:
    };
}

#endif /* !MATE_HPP_ */
