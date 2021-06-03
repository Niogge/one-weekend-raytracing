#pragma once
#include "Material.h";
BEGIN_NAMESPACE
class metal : public material
{
public:
	metal(const RGBColor& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered)const override;
public:
	RGBColor albedo;
};
END_NAMESPACE
