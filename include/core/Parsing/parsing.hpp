/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** parsing
*/

#ifndef PARSING_HPP_
    #define PARSING_HPP_

#include <libconfig.h++>
#include "IPrimitives.hpp"
#include "Vector3.hpp"

#define CAMERA_FILE "assets/configuration/raytracer_config.cfg"

enum MaterialType {
    MATE,
    METAL,
    GLASS
};

enum TextureType {
    BASE,
    CHESS
};

struct CameraSettings {
    double width;
    double height;
    Math::Vector3 pos;
    Math::Vector3 rotation;
    double fov;
    int maxDepth;
    int samplesPerPixel;
};

struct BaseTextureSettings {
    Math::Vector3 color;
};

struct ChessTextureSettings {
    Math::Vector3 color1;
    Math::Vector3 color2;
};

struct MateMaterial {
    TextureType textureType;
    struct ChessTextureSettings chessTextureSettings;
    struct BaseTextureSettings baseTextureSettings;
};

struct MetalMaterial {
    Math::Vector3 color;
    double fuzz;
};

struct GlassMaterial {
    double refraction;
};

struct MaterialSettings {
    MaterialType type;
    struct MateMaterial mateMaterial;
    struct MetalMaterial metalMaterial;
    struct GlassMaterial glassMaterial;
};

struct AmbiantLightSettings {
    double intensity;
};

struct DirectionalLightSettings {
    std::string direction;
    std::array<double, 5> points;
    double intensity;
};

struct PointLightSettings {
    Math::Vector3 pos;
    double radius;
    double intensity;
};

struct LightSettings {
    struct AmbiantLightSettings ambiantLightSetting;
    std::vector<struct DirectionalLightSettings> directionalLightSettings;
    std::vector<struct PointLightSettings> pointLightSettings;
};

struct SphereSettings {
    Math::Vector3 center;
    Math::Vector3 rotation;
    double radius;
    MaterialSettings material;
};

struct PlaneSettings {
    std::string axis;
    Math::Vector3 rotation;
    double a;
    double b;
    double c;
    double d;
    double k;
    MaterialSettings material;
};

struct ConeSettings {
    Math::Vector3 center;
    Math::Vector3 rotation;
    double radius;
    double height;
    MaterialSettings material;
};

struct CylinderSettings {
    Math::Vector3 center;
    Math::Vector3 rotation;
    double radius;
    double height;
    MaterialSettings material;
};

struct PrimitivesSettings {
    std::vector<SphereSettings> sphereSettings;
    std::vector<PlaneSettings> planeSettings;
    std::vector<ConeSettings> coneSettings;
    std::vector<CylinderSettings> cylinderSettings;
};

CameraSettings default_camera_settings();
MaterialSettings default_material_settings();
CameraSettings parseCameraSettings(std::string filename);
PrimitivesSettings parsePrimitivesSettings(std::string filename);
LightSettings parseLightSettings(std::string filename);
MaterialSettings parseMaterialSettings(const libconfig::Setting &material);

#endif /* !PARSING_HPP_ */
