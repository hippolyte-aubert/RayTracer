/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** parsing
*/

#include "parsing.hpp"

#include <libconfig.h++>

CameraSettings default_camera_settings() {
    CameraSettings settings;

    settings.width = 800;
    settings.height = 600;
    settings.pos = Math::Vector3(0.0, 0.0, 1.0);
    settings.rotation = Math::Vector3(0.0, 0.0, 0.0);
    settings.fov = 75;
    return settings;
}

MaterialSettings default_material_settings() {
    MaterialSettings settings;

    settings.type = MATE;
    settings.mateMaterial.textureType = BASE;
    settings.mateMaterial.baseTextureSettings.color = Math::Vector3(0.05, 0.05, 0.65);
    return settings;
}

CameraSettings parseCameraSettings(std::string filename) {
    CameraSettings cameraSettings = default_camera_settings();
    try {
        libconfig::Config cfg;
        cfg.readFile(filename.c_str());
        const libconfig::Setting& camera = cfg.lookup("camera");
        const libconfig::Setting& resolution = camera["resolution"];
        cameraSettings.width = resolution[0];
        cameraSettings.height = resolution[1];
        const libconfig::Setting& pos = camera["position"];
        cameraSettings.pos = Math::Vector3(pos[0], pos[1], pos[2]);
        const libconfig::Setting& rotation = camera["rotation"];
        cameraSettings.rotation = Math::Vector3(rotation[0], rotation[1], rotation[2]);
        camera.lookupValue("fov", cameraSettings.fov);
        camera.lookupValue("max_depth", cameraSettings.maxDepth);
        camera.lookupValue("samples_per_pixel", cameraSettings.samplesPerPixel);
    } catch (const libconfig::ParseException& e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
    } catch (const libconfig::SettingNotFoundException& e) {
        std::cerr << "Setting not found in configuration file at : " << e.getPath() << e.what() << std::endl;
    } catch (const libconfig::SettingTypeException& e) {
        std::cerr << "Setting has incorrect type at : " << e.getPath() << e.what() << std::endl;
    }
    return cameraSettings;
}

PrimitivesSettings parsePrimitivesSettings(std::string filename) {
    PrimitivesSettings primitivesSettings;
    try {
        libconfig::Config cfg;
        cfg.readFile(filename.c_str());
        const libconfig::Setting& primitives = cfg.lookup("primitives");
        if (primitives.exists("spheres")) {
            libconfig::Setting& sphereSetting = primitives["spheres"];
            for (const auto& sphere : sphereSetting) {
                SphereSettings sphereSettings;
                const libconfig::Setting& center = sphere["position"];
                sphereSettings.center = Math::Vector3(center[0], center[1], center[2]);
                const libconfig::Setting& rotation = sphere["rotation"];
                sphereSettings.rotation = Math::Vector3(rotation[0], rotation[1], rotation[2]);
                sphere.lookupValue("radius", sphereSettings.radius);
                sphereSettings.material = parseMaterialSettings(sphere["material"]);
                primitivesSettings.sphereSettings.push_back(sphereSettings);
            }
        }
        if (primitives.exists("planes")) {
            libconfig::Setting& planeSetting = primitives["planes"];
            for (const auto& plane : planeSetting) {
                PlaneSettings planeSettings;
                plane.lookupValue("axis", planeSettings.axis);\
                const libconfig::Setting& rotation = plane["rotation"];
                planeSettings.rotation = Math::Vector3(rotation[0], rotation[1], rotation[2]);
                plane.lookupValue("a", planeSettings.a);
                plane.lookupValue("b", planeSettings.b);
                plane.lookupValue("c", planeSettings.c);
                plane.lookupValue("d", planeSettings.d);
                plane.lookupValue("k", planeSettings.k);
                planeSettings.material = parseMaterialSettings(plane["material"]);
                primitivesSettings.planeSettings.push_back(planeSettings);
            }
        }
        if (primitives.exists("cones")) {
            libconfig::Setting& coneSetting = primitives["cones"];
            for (const auto& cone : coneSetting) {
                ConeSettings coneSettings;
                const libconfig::Setting& center = cone["position"];
                coneSettings.center = Math::Vector3(center[0], center[1], center[2]);
                const libconfig::Setting& rotation = cone["rotation"];
                coneSettings.rotation = Math::Vector3(rotation[0], rotation[1], rotation[2]);
                cone.lookupValue("radius", coneSettings.radius);
                cone.lookupValue("height", coneSettings.height);
                coneSettings.material = parseMaterialSettings(cone["material"]);
                primitivesSettings.coneSettings.push_back(coneSettings);
            }
        }
        if (primitives.exists("cylinders")) {
            libconfig::Setting& cylinderSetting = primitives["cylinders"];
            for (const auto& cylinder : cylinderSetting) {
                CylinderSettings cylinderSettings;
                const libconfig::Setting& center = cylinder["position"];
                cylinderSettings.center = Math::Vector3(center[0], center[1], center[2]);
                const libconfig::Setting& rotation = cylinder["rotation"];
                cylinderSettings.rotation = Math::Vector3(rotation[0], rotation[1], rotation[2]);
                cylinder.lookupValue("radius", cylinderSettings.radius);
                cylinder.lookupValue("height", cylinderSettings.height);
                cylinderSettings.material = parseMaterialSettings(cylinder["material"]);
                primitivesSettings.cylinderSettings.push_back(cylinderSettings);
            }
        }
    } catch (const libconfig::ParseException& e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
    } catch (const libconfig::SettingNotFoundException& e) {
        std::cerr << "Setting not found in configuration file is: " << e.getPath() << std::endl;
    } catch (const libconfig::SettingTypeException& e) {
        std::cerr << "Setting has incorrect type is: " << e.getPath() << std::endl;
    }
    return primitivesSettings;
}

MaterialSettings parseMaterialSettings(const libconfig::Setting& material) {
    MaterialSettings materialSettings;
    const libconfig::Setting& type = material["type"];
    std::string typeStr = type;
    if (typeStr == "mate") {
        materialSettings.type = MATE;
        const libconfig::Setting& texture = material["texture"]["type"];
        std::string textureStr = texture;
        if (textureStr == "base") {
            materialSettings.mateMaterial.textureType = BASE;
            const libconfig::Setting& color = material["texture"]["color"];
            materialSettings.mateMaterial.baseTextureSettings.color = Math::Vector3(color[0], color[1], color[2]);
        }
        if (textureStr == "chess") {
            materialSettings.mateMaterial.textureType = CHESS;
            const libconfig::Setting& color1 = material["texture"]["color1"];
            materialSettings.mateMaterial.chessTextureSettings.color1 = Math::Vector3(color1[0], color1[1], color1[2]);
            const libconfig::Setting& color2 = material["texture"]["color2"];
            materialSettings.mateMaterial.chessTextureSettings.color2 = Math::Vector3(color2[0], color2[1], color2[2]);
        }
    } else if (typeStr == "metal") {
        materialSettings.type = METAL;
        material.lookupValue("fuzz", materialSettings.metalMaterial.fuzz);
        const libconfig::Setting& color = material["color"];
        materialSettings.metalMaterial.color = Math::Vector3(color[0], color[1], color[2]);
    } else if (typeStr == "glass") {
        materialSettings.type = GLASS;
        material.lookupValue("refractive_index", materialSettings.glassMaterial.refraction);
    } else {
        return default_material_settings();
    }
    return materialSettings;
}

LightSettings parseLightSettings(std::string filename) {
    LightSettings lightSettings;
    try {
        libconfig::Config cfg;
        cfg.readFile(filename.c_str());
        const libconfig::Setting& lights = cfg.lookup("lights");

        libconfig::Setting& ambientLight = lights["ambient"];
        AmbiantLightSettings ambient;
        ambientLight.lookupValue("intensity", ambient.intensity);
        lightSettings.ambiantLightSetting = ambient;
        if (lights.exists("directional")) {
            libconfig::Setting& directionalLightSetting = lights["directional"];
            for (const auto& directional : directionalLightSetting) {
                DirectionalLightSettings directionalLight;
                directional.lookupValue("direction", directionalLight.direction);
                const libconfig::Setting& points = directional["points"];
                directionalLight.points = std::array<double, 5>{points[0], points[1], points[2], points[3], points[4]};
                directional.lookupValue("intensity", directionalLight.intensity);
                lightSettings.directionalLightSettings.push_back(directionalLight);
            }
        }
        if (lights.exists("points")) {
            libconfig::Setting& pointLightSetting = lights["points"];
            for (const auto& point : pointLightSetting) {
                PointLightSettings pointLight;
                const libconfig::Setting& position = point["position"];
                pointLight.pos = Math::Vector3(position[0], position[1], position[2]);
                point.lookupValue("intensity", pointLight.intensity);
                point.lookupValue("radius", pointLight.radius);
                lightSettings.pointLightSettings.push_back(pointLight);
            }
        }
    } catch (const libconfig::ParseException& e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
    } catch (const libconfig::SettingNotFoundException& e) {
        std::cerr << "Setting not found in configuration file is: " << e.getPath() << std::endl;
    } catch (const libconfig::SettingTypeException& e) {
        std::cerr << "Setting has incorrect type is: " << e.getPath() << std::endl;
    }
    return lightSettings;
}
