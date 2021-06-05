#include "Model.h"
#include "../Utils/Math/Ray.h"
#define EPSILON 0.000001f
USE_NAMESPACE(Model)::Model(const std::string modelPath, vec3 c, std::shared_ptr<material> m) 
	: position(c), mat_ptr(m), object(wobj_from_file(modelPath.c_str()))
{
	

}
bool rayTriangle_intersection(const USE_NAMESPACE(Ray)& r, const vec3& v0, const vec3& v1, const vec3& v2, float& t_result)
{
	vec3 e1, e2, h, s, q;
	e1 = v1 - v0;
	e2 = v2 - v0;

	h = cross(r.dir, e2);
	float det = dot(h, e1);

	if (det < EPSILON)
	{

		return false;
	}
	float f = 1 / det;
	
	s = r.orig - v0;
	float u = f * dot(s, h);
	if (u < 0.0 || u>1.0)
	{
		return false;
	}

	q = cross(s, e1);
	float v = f * dot(r.dir, q);

	if (v < 0.0 || u + v>1.0)
	{
		return false;
	}
	t_result = f * dot(e2, q);
	return true;
}

bool USE_NAMESPACE(Model)::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{

	float t_hit_min = 100000000;
	bool found = false;
	for (int i = 0; i < object.get()->triangles_count; i++)
	{
		float t_result;
		wobj_triangle t = object.get()->triangles[i];
		vec3 v0 = from_wobj_to_vec3(t.v1.position);
		vec3 v1 = from_wobj_to_vec3(t.v2.position);
		vec3 v2 = from_wobj_to_vec3(t.v3.position);
		if (rayTriangle_intersection(r, v0, v1, v2, t_result))
		{
			if (t_result < t_max && t_result>t_min)
			{
				if (t_result < t_hit_min)
				{
					rec.p = r.at(t_result);
					rec.normal = from_wobj_to_vec3(t.v1.normal);
					rec.mat_ptr = mat_ptr;
					rec.t = t_result;
					rec.set_face_normal(r, rec.normal);
					found = true;
				}
			}
		}
	}
	return found;
}
