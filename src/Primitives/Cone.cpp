/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** Cone
    */

    #include "Cone.hpp"

    namespace RayTracer {
    Cone::Cone() {
        type = "Cone";
    }

    Cone::Cone(const Math::Vector3 &center, double radius, double height, std::shared_ptr<IMaterial> mat) : center(center), radius(radius), height(height), material(mat) {
        type = "Cone";
    }

    Cone::~Cone() {
    }

    bool Cone::hits(const Ray &ray, double t_min, double t_max, hit &record) const {
        Math::Vector3 oc = ray.origin - center;
        double A = oc.x;
        double B = oc.z;
        double D = height - ray.origin.y + center.y;

        double tan2 = (radius / height) * (radius / height);
        double a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z) - (tan2 * (ray.direction.y * ray.direction.y));
        double b = (2 * A * ray.direction.x) + (2 * B * ray.direction.z) + (2 * tan2 * D * ray.direction.y);
        double c = (A * A) + (B * B) - (tan2 * (D * D));
        double d = b * b - 4 * a * c;
        if (d < 0)
            return false;
        double root1 = (-b - sqrt(d)) / (2.0 * a);
        double root2 = (-b + sqrt(d)) / (2.0 * a);
        double y1 = ray.origin.y + root1 * ray.direction.y;
        double y2 = ray.origin.y + root2 * ray.direction.y;

        double root;
        Math::Vector3 normal;

        if ((y1 >= center.y) && (y1 <= center.y + height)) {
            root = root1;
            normal = Math::Vector3(A + root1 * ray.direction.x, radius, B + root1 * ray.direction.z) / radius;
        } else if ((y2 >= center.y) && (y2 <= center.y + height)) {
            root = root2;
            normal = Math::Vector3(A + root2 * ray.direction.x, radius, B + root2 * ray.direction.z) / radius;
        } else
            return false;
        if (root < t_min || root > t_max)
            return false;
        record.t = root;
        record.point = ray.pointAt(record.t);
        record.normal = (record.point - center) / radius;
        Math::Vector3 outward_normal = (record.point - center) / radius;
        record.set_face_normal(ray, outward_normal);
        get_cone_uv(outward_normal, record.u, record.v);
        record.material = material;
        return true;
    }

    bool Cone::bounding_box(double time0, double time1, BoundingBoxes &output_box) const {
        output_box = BoundingBoxes(center - Math::Vector3(radius, height, radius), center + Math::Vector3(radius, height, radius));
        return true;
    }

    void Cone::get_cone_uv(const Math::Vector3 &p, double &u, double &v) {
        double phi = atan2(p.z, p.x);
        u = 1 - (phi + M_PI) / (2 * M_PI);
        v = (p.y + 1) / 2;
    }

    std::string Cone::getType() const {
        return type;
    }
}  // namespace RayTracer
