#pragma once
#include "Material.h";
BEGIN_NAMESPACE
class dielectric : public material
{
public:
	dielectric(const RGBColor& a, double ir) : albedo(a), index_refraction(ir) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, RGBColor& attenuation, Ray& scattered)const override;
public:
	RGBColor albedo;
	double index_refraction;
private:
	static double reflectance(double cosine, double ref_idx);
};
END_NAMESPACE
