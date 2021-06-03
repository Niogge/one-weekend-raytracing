#pragma once
#include "Material.h";
BEGIN_NAMESPACE
class lambertian : public material
{
public:
	lambertian(const RGBColor& a):albedo(a){}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered)const override;
public:
	RGBColor albedo;
};
END_NAMESPACE