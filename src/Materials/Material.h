#pragma once
#include "../Utils/FWDUtils.h"
#include "../Utils/Math/Ray.h"
#include "../Hittables/Hittable.h"
BEGIN_NAMESPACE

class material
{
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered) const = 0;
};
END_NAMESPACE