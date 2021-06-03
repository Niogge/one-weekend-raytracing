#pragma once
#include "Material.h";
BEGIN_NAMESPACE
class metal : public material
{
public:
	metal(const RGBColor& a, double f=0) : albedo(a), fuzz(f<1?f:1) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered)const override;
public:
	RGBColor albedo;
	double fuzz;
};
END_NAMESPACE
