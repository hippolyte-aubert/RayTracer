/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** SolidColor
*/

#include "BaseTexture.hpp"

namespace RayTracer {
    BaseTexture::BaseTexture()
    {
    }

    BaseTexture::BaseTexture(Math::Vector3 c) : _color(c)
    {
    }

    BaseTexture::BaseTexture(double red, double green, double blue) : _color(red, green, blue)
    {
    }

    BaseTexture::~BaseTexture()
    {
    }

    Math::Vector3 BaseTexture::value(double u, double v, const Math::Vector3 &p) const
    {
        return _color;
    }
}
