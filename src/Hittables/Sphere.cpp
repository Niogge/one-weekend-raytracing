#include "Sphere.h"
#include "../Utils/Math/Ray.h"
//double rt_one_w::Sphere::ray_sphere_intersection(const Ray& r) const
//{
//    vec3 OC = r.origin() - center;
//    auto a = r.direction().length_squared();
//    auto half_b =  dot(OC, r.direction());
//    auto c = OC.length_squared() - radius * radius;
//    auto discriminant = half_b * half_b - a * c;
//
//    if (discriminant < 0)
//    {
//        return -1.0;
//    }
//    else
//    {
//        return (-half_b - sqrt(discriminant)) / a;
//    }
//}

bool USE_NAMESPACE(Sphere)::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 OC = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(OC, r.direction());
	auto c = OC.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return false;
	auto sqrtd = sqrt(discriminant);
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root ;
	rec.p = r.at(root);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}
