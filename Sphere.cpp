#include "Sphere.h"
#include "Ray.h"
double rt_one_w::Sphere::ray_sphere_intersection(const Ray& r) const
{
    vec3 OC = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(OC, r.direction());
    auto c = dot(OC, OC) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

