#include "HittableList.h"

USE_NAMESPACE(hittable_list)::hittable_list(shared_ptr<hittable> object)
{
	add(object);
}

void USE_NAMESPACE(hittable_list)::clear()
{
	objects.clear();
}

void USE_NAMESPACE(hittable_list)::add(shared_ptr<hittable> object)
{
	objects.push_back(object);
}

bool USE_NAMESPACE(hittable_list)::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_record;
	bool hit_any = false;
	auto closest_so_far = t_max;
	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_record))
		{
			hit_any = true;
			closest_so_far = temp_record.t;
			rec = temp_record;
		}
	}
	return hit_any;
}
