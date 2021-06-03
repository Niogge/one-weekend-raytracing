#include "Lambertian.h"

bool USE_NAMESPACE(lambertian)::scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered) const
{
	auto scatter_direction = rec.normal + random_unit_vector();
	if (scatter_direction.near_zero()) //avoid zero scatter direction 
	{
		scatter_direction = rec.normal;
	}
	scattered = Ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}
