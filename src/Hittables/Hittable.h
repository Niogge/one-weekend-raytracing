#pragma once
#include "../Utils/IOUtils.h"
#include "../Utils/Math/Ray.h"
#include <memory>
BEGIN_NAMESPACE
FWD_DECL(material)
struct hit_record
{
	point3 p;
	vec3 normal;
	std::shared_ptr<material> mat_ptr;
	double t;
	bool front_face;

	inline void set_face_normal(const Ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};
class hittable
{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

END_NAMESPACE