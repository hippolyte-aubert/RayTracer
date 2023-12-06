/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** ChessTexture
*/

#ifndef CHESSTEXTURE_HPP_
    #define CHESSTEXTURE_HPP_

    #include "ITexture.hpp"
    #include "BaseTexture.hpp"

namespace RayTracer {
    class ChessTexture : public ITexture {
        public:
            ChessTexture();
            ChessTexture(std::shared_ptr<ITexture> even, std::shared_ptr<ITexture> odd);
            ChessTexture(Math::Vector3 c1, Math::Vector3 c2);
            ~ChessTexture();

            Math::Vector3 value(double u, double v, const Math::Vector3 &p) const override;

            std::shared_ptr<ITexture> even;
            std::shared_ptr<ITexture> odd;
    };
}

#endif /* !CHESSTEXTURE_HPP_ */
