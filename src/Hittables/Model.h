#pragma once
#include "../Utils/FWDUtils.h"
#include "../Utils/Math/vec3.h"
#include "Hittable.h"
#include "../Includes/wobj_kdtree.h"
BEGIN_NAMESPACE
class Model :public hittable
{
public:
	Model() :position(vec3(0, 0, 0)), object(nullptr) {};
	~Model();
	Model(const std::string modelPath, vec3 c, std::shared_ptr<material> m);
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
public:
	point3 position;
	std::shared_ptr<material> mat_ptr;
private:
	wobj_kdtree* object;
};
END_NAMESPACE
