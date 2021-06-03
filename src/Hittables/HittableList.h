#pragma once
#include "../Utils/FWDUtils.h"
#include "../Utils/Math/Ray.h"
#include "Hittable.h"
#include <memory>
#include <vector>

BEGIN_NAMESPACE
using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable
{
public:
	hittable_list(){}
	hittable_list(shared_ptr<hittable> object);
	void clear();
	void add(shared_ptr<hittable> object);
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
public:
	std::vector<shared_ptr<hittable>> objects;
};

END_NAMESPACE