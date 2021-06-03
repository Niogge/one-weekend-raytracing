#include "Dielectric.h"

bool USE_NAMESPACE(dielectric)::scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered) const
{
	attenuation = albedo;
	double ref_ratio = rec.front_face ? (1.0 / index_refraction) : index_refraction;
	vec3 unit_direction = r_in.direction().normalized();
	double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	bool cannot_refract = ref_ratio * sin_theta > 1.0;
	vec3 direction;
	if (cannot_refract || reflectance(cos_theta, ref_ratio)>random_double())
	{
		direction = reflect(unit_direction, rec.normal);
	}
	else
	{
		direction = refract(unit_direction, rec.normal, ref_ratio);
	}
	scattered = Ray(rec.p, direction);
	return true;
}

double USE_NAMESPACE(dielectric)::reflectance(double cosine, double ref_idx)
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
