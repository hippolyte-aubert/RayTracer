/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_

    #include "Vector3.hpp"
    #include <memory>

namespace RayTracer {
    class ITexture {
        public:
            virtual ~ITexture() = default;

            virtual Math::Vector3 value(double u, double v, const Math::Vector3 &p) const = 0;

        protected:
        private:
    };
}

#endif /* !TEXTURE_HPP_ */
