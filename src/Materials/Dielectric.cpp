#include "Dielectric.h"

bool USE_NAMESPACE(dielectric)::scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered) const
{
	attenuation = albedo;
	double ref_ratio = rec.front_face ? (1.0 / index_refraction) : index_refraction;
	vec3 unit_direction = r_in.direction().normalized();
	vec3 refracted = refract(unit_direction, rec.normal, ref_ratio);
	scattered = Ray(rec.p, refracted);
	return true;
}
