#include "Metal.h"

bool USE_NAMESPACE(metal)::scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered) const
{
	vec3 reflected = reflect(r_in.direction().normalized(), rec.normal);
	scattered = Ray(rec.p, reflected);
	attenuation = albedo;
	return(dot(scattered.direction(), rec.normal) > 0);
}
