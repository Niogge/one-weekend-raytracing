#include "Model.h"
#include "../Utils/Math/Ray.h"
#define EPSILON 0.000001f
USE_NAMESPACE(Model)::~Model()
{
	wobj_kdtree_destroy(object);
}
USE_NAMESPACE(Model)::Model(const std::string modelPath, vec3 c, std::shared_ptr<material> m)
	: position(c), mat_ptr(m), object(nullptr)
{
	object = wobj_kdtree_from_file(modelPath.c_str(),6);

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
	wobj_hit_result hit_rex;

	if (ray_box_intersection(from_vec3_to_wobj(r.orig), from_vec3_to_wobj(r.dir), object, &hit_rex) == 1)
	{
		rec.p = r.at(hit_rex.t_hit);
		rec.normal = from_wobj_to_vec3(hit_rex.tris->v1.normal);
		rec.mat_ptr = mat_ptr;
		rec.t = hit_rex.t_hit;
		rec.set_face_normal(r, rec.normal);
		return true;
	}

	return false;
	
}
