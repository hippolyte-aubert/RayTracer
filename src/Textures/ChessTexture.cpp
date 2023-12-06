/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** ChessTexture
*/

#include "ChessTexture.hpp"

namespace RayTracer {
    ChessTexture::ChessTexture()
    {
    }

    ChessTexture::ChessTexture(std::shared_ptr<ITexture> even, std::shared_ptr<ITexture> odd) : even(even), odd(odd)
    {
    }

    ChessTexture::ChessTexture(Math::Vector3 c1, Math::Vector3 c2) : even(std::make_shared<BaseTexture>(c1)), odd(std::make_shared<BaseTexture>(c2))
    {
    }

    ChessTexture::~ChessTexture()
    {
    }

    Math::Vector3 ChessTexture::value(double u, double v, const Math::Vector3 &p) const
    {
        auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
        if (sines < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }
}
