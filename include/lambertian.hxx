#ifndef LAMBERTIAN_HXX_
#define LAMBERTIAN_HXX_

#include "hitable.h"
#include "other.h"

namespace AFei
{
    class lambertian: public material
    {
    public:
        AFei::vec3<float> albedo;

    public:
        lambertian();
        lambertian(const AFei::vec3<float> &lambertian_albedo);

    public:
        virtual bool scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> &attenuation, AFei::ray<float> &r_out) const;
        virtual AFei::ray<float> reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const;
    };
};

AFei::lambertian::lambertian()
{
    albedo = vec3<float>(0.5f, 0.5f, 0.5f);
}

AFei::lambertian::lambertian(const AFei::vec3<float> &lambertian_albedo)
{
    albedo = lambertian_albedo;
}

bool AFei::lambertian::scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> &attenuation, AFei::ray<float> &r_out) const
{
    r_out = reflect(r_in, rec);
    attenuation = this->albedo;
    return true;
}

AFei::ray<float> AFei::lambertian::reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const
{
    auto target = vec3<float>(generateRandom(-1.0f, 1.0f), generateRandom(-1.0f, 1.0f), generateRandom(-1.0f, 1.0f));
    target += rec.intersectPoint + rec.normal;
    auto r_out = ray<float>(rec.intersectPoint, (target - rec.intersectPoint).normal_vector());
    return r_out;
}

#endif