/*
** EPITECH PROJECT, 2023
** raytracer bs
** File description:
** main
*/

#include <iostream>

#include "Box.hpp"
#include "Camera.hpp"
#include "ChessTexture.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "DiffuseLight.hpp"
#include "Glass.hpp"
#include "Mate.hpp"
#include "Metal.hpp"
#include "Plane.hpp"
#include "RotateX.hpp"
#include "RotateY.hpp"
#include "RotateZ.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Translate.hpp"
#include "Utils.hpp"
#include "Vector3.hpp"
#include "parsing.hpp"

void write_color(std::ostream &out, Math::Vector3 pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    auto scale = 1.0 / samples_per_pixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    out << static_cast<int>(256 * Math::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Math::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Math::clamp(b, 0.0, 0.999)) << '\n';
}

Math::Vector3 ray_color(const RayTracer::Ray &r, const Math::Vector3 &bg_color, RayTracer::Scene &scene, int depth) {
    RayTracer::hit record;

    if (depth <= 0)
        return Math::Vector3(0, 0, 0);
    if (!scene.hits(r, 0.001, Math::infinity, record))
        return bg_color;
    RayTracer::Ray scattered;
    Math::Vector3 attenuation;
    Math::Vector3 emitted = record.material->emitted(record.u, record.v, record.point);

    if (!record.material->scatter(r, record, attenuation, scattered))
        return emitted;
    return emitted + attenuation * ray_color(scattered, bg_color, scene, depth - 1);
}

std::shared_ptr<RayTracer::RotateZ> sphereFactory(const SphereSettings &sphereSettings, std::shared_ptr<RayTracer::IMaterial> material)
{
    auto sphe = std::make_shared<RayTracer::Sphere>(sphereSettings.center, sphereSettings.radius, material);
    auto x = std::make_shared<RayTracer::RotateX>(sphe, sphereSettings.rotation.x);
    auto y = std::make_shared<RayTracer::RotateY>(x, sphereSettings.rotation.y);
    auto z = std::make_shared<RayTracer::RotateZ>(y, sphereSettings.rotation.z);
    return z;
}

std::shared_ptr<RayTracer::Plane> planeFactory(const PlaneSettings &planeSettings, std::shared_ptr<RayTracer::IMaterial> material)
{
    auto plane = std::make_shared<RayTracer::Plane>(planeSettings.axis, planeSettings.a, planeSettings.b, planeSettings.c, planeSettings.d, planeSettings.k, material);
    return plane;
}

std::shared_ptr<RayTracer::RotateZ> coneFactory(const ConeSettings &coneSettings, std::shared_ptr<RayTracer::IMaterial> material)
{
    auto cone = std::make_shared<RayTracer::Cone>(coneSettings.center, coneSettings.radius, coneSettings.height, material);
    auto x = std::make_shared<RayTracer::RotateX>(cone, coneSettings.rotation.x);
    auto y = std::make_shared<RayTracer::RotateY>(x, coneSettings.rotation.y);
    auto z = std::make_shared<RayTracer::RotateZ>(y, coneSettings.rotation.z);
    return z;
}

std::shared_ptr<RayTracer::RotateZ> cylinderFactory(const CylinderSettings &cylinderSettings, std::shared_ptr<RayTracer::IMaterial> material)
{
    auto cylinder = std::make_shared<RayTracer::Cylinder>(cylinderSettings.center, cylinderSettings.radius, cylinderSettings.height, material);
    auto x = std::make_shared<RayTracer::RotateX>(cylinder, cylinderSettings.rotation.x);
    auto y = std::make_shared<RayTracer::RotateY>(x, cylinderSettings.rotation.y);
    auto z = std::make_shared<RayTracer::RotateZ>(y, cylinderSettings.rotation.z);
    return z;
}

RayTracer::Scene sceneBuilder(std::string filename, Math::Vector3 &bgColor)
{
    PrimitivesSettings primitivesSettings = parsePrimitivesSettings(filename);
    LightSettings lightSettings = parseLightSettings(filename);

    RayTracer::Scene scene;

    for (const auto &sphere : primitivesSettings.sphereSettings) {
        if (sphere.material.type == MATE) {
            if (sphere.material.mateMaterial.textureType == BASE) {
                auto base = std::make_shared<RayTracer::BaseTexture>(sphere.material.mateMaterial.baseTextureSettings.color);
                scene.add(sphereFactory(sphere, std::make_shared<RayTracer::Mate>(base)));
            } else if (sphere.material.mateMaterial.textureType == CHESS) {
                auto chess = std::make_shared<RayTracer::ChessTexture>(sphere.material.mateMaterial.chessTextureSettings.color1, sphere.material.mateMaterial.chessTextureSettings.color2);
                scene.add(sphereFactory(sphere, std::make_shared<RayTracer::Mate>(chess)));
            }
        }
        if (sphere.material.type == METAL) {
            auto metal = std::make_shared<RayTracer::Metal>(sphere.material.metalMaterial.color, sphere.material.metalMaterial.fuzz);
            scene.add(sphereFactory(sphere, metal));
        }
        if (sphere.material.type == GLASS) {
            auto glass = std::make_shared<RayTracer::Glass>(sphere.material.glassMaterial.refraction);
            scene.add(sphereFactory(sphere, glass));
        }
    }
    for (const auto &plane : primitivesSettings.planeSettings) {
        if (plane.material.type == MATE) {
            if (plane.material.mateMaterial.textureType == BASE) {
                auto base = std::make_shared<RayTracer::BaseTexture>(plane.material.mateMaterial.baseTextureSettings.color);
                scene.add(planeFactory(plane, std::make_shared<RayTracer::Mate>(base)));
            } else if (plane.material.mateMaterial.textureType == CHESS) {
                auto chess = std::make_shared<RayTracer::ChessTexture>(plane.material.mateMaterial.chessTextureSettings.color1, plane.material.mateMaterial.chessTextureSettings.color2);
                scene.add(planeFactory(plane, std::make_shared<RayTracer::Mate>(chess)));
            }
        }
        if (plane.material.type == METAL) {
            auto metal = std::make_shared<RayTracer::Metal>(plane.material.metalMaterial.color, plane.material.metalMaterial.fuzz);
            scene.add(planeFactory(plane, metal));
        }
        if (plane.material.type == GLASS) {
            auto glass = std::make_shared<RayTracer::Glass>(plane.material.glassMaterial.refraction);
            scene.add(planeFactory(plane, glass));
        }
    }
    for (const auto &cone : primitivesSettings.coneSettings) {
        if (cone.material.type == MATE) {
            if (cone.material.mateMaterial.textureType == BASE) {
                auto base = std::make_shared<RayTracer::BaseTexture>(cone.material.mateMaterial.baseTextureSettings.color);
                scene.add(coneFactory(cone, std::make_shared<RayTracer::Mate>(base)));
            } else if (cone.material.mateMaterial.textureType == CHESS) {
                auto chess = std::make_shared<RayTracer::ChessTexture>(cone.material.mateMaterial.chessTextureSettings.color1, cone.material.mateMaterial.chessTextureSettings.color2);
                scene.add(coneFactory(cone, std::make_shared<RayTracer::Mate>(chess)));
            }
        }
        if (cone.material.type == METAL) {
            auto metal = std::make_shared<RayTracer::Metal>(cone.material.metalMaterial.color, cone.material.metalMaterial.fuzz);
            scene.add(coneFactory(cone, metal));
        }
        if (cone.material.type == GLASS) {
            auto glass = std::make_shared<RayTracer::Glass>(cone.material.glassMaterial.refraction);
            scene.add(coneFactory(cone, glass));
        }
    }
    for (const auto &cylinder : primitivesSettings.cylinderSettings) {
        if (cylinder.material.type == MATE) {
            if (cylinder.material.mateMaterial.textureType == BASE) {
                auto base = std::make_shared<RayTracer::BaseTexture>(cylinder.material.mateMaterial.baseTextureSettings.color);
                scene.add(cylinderFactory(cylinder, std::make_shared<RayTracer::Mate>(base)));
            } else if (cylinder.material.mateMaterial.textureType == CHESS) {
                auto chess = std::make_shared<RayTracer::ChessTexture>(cylinder.material.mateMaterial.chessTextureSettings.color1, cylinder.material.mateMaterial.chessTextureSettings.color2);
                scene.add(cylinderFactory(cylinder, std::make_shared<RayTracer::Mate>(chess)));
            }
        }
        if (cylinder.material.type == METAL) {
            auto metal = std::make_shared<RayTracer::Metal>(cylinder.material.metalMaterial.color, cylinder.material.metalMaterial.fuzz);
            scene.add(cylinderFactory(cylinder, metal));
        }
        if (cylinder.material.type == GLASS) {
            auto glass = std::make_shared<RayTracer::Glass>(cylinder.material.glassMaterial.refraction);
            scene.add(cylinderFactory(cylinder, glass));
        }
    }
    for (const auto &lights : lightSettings.directionalLightSettings) {
        auto light = std::make_shared<RayTracer::DiffuseLight>(Math::Vector3(lights.intensity, lights.intensity, lights.intensity));
        scene.add(std::make_shared<RayTracer::Plane>(lights.direction, lights.points[0], lights.points[1], lights.points[2], lights.points[3], lights.points[4], light));
    }
    for (const auto &lights : lightSettings.pointLightSettings) {
        auto light = std::make_shared<RayTracer::DiffuseLight>(Math::Vector3(lights.intensity, lights.intensity, lights.intensity));
        scene.add(std::make_shared<RayTracer::Sphere>(lights.pos, lights.radius, light));
    }
    bgColor = Math::Vector3(bgColor.x * lightSettings.ambiantLightSetting.intensity, bgColor.y * lightSettings.ambiantLightSetting.intensity, bgColor.z * lightSettings.ambiantLightSetting.intensity);

    return scene;
}

void raytracer(std::string configfile) {
    CameraSettings cameraSettings = parseCameraSettings(configfile);
    const auto aspect_ratio = cameraSettings.width / cameraSettings.height;
    const int image_width = static_cast<int>(cameraSettings.width);
    const int image_height = static_cast<int>(cameraSettings.height);
    const int samples_per_pixel = cameraSettings.samplesPerPixel;
    const int max_depth = cameraSettings.maxDepth;

    // World
    Math::Vector3 bgColor(0, 0, 0);
    RayTracer::Scene scene = sceneBuilder(configfile, bgColor);

    RayTracer::Camera camera(aspect_ratio, cameraSettings.fov, cameraSettings.pos, cameraSettings.rotation, Math::Vector3(0, 1, 0));

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
    for (int y = image_height - 1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; x++) {
            Math::Vector3 pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (x + Math::random_double()) / (image_width - 1);
                auto v = (y + Math::random_double()) / (image_height - 1);
                RayTracer::Ray ray = camera.ray(u, v);
                pixel_color += ray_color(ray, bgColor, scene, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./raytracer <SCENE_FILE>\n"
                  << "  SCENE_FILE: path scene configuration\n";
        exit(84);
    } else if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        std::cerr << "Usage: ./raytracer <SCENE_FILE>\n"
                  << "  SCENE_FILE: path scene configuration\n";
        return 0;
    } else
        raytracer(argv[1]);
    return 0;
}
