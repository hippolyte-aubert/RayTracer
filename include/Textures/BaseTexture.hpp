/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** SolidColor
*/

#ifndef SOLIDCOLOR_HPP_
    #define SOLIDCOLOR_HPP_

    #include "ITexture.hpp"

namespace RayTracer {
    class BaseTexture : public ITexture {
        public:
            BaseTexture();
            BaseTexture(Math::Vector3 c);
            BaseTexture(double red, double green, double blue);
            ~BaseTexture();

            Math::Vector3 value(double u, double v, const Math::Vector3 &p) const override;

        private:
            Math::Vector3 _color;
    };
}

#endif /* !SOLIDCOLOR_HPP_ */
