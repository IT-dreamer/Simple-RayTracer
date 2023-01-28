#ifndef METAL_HXX_
#define METAL_HXX_

#include "hitable.h"

namespace AFei
{
    class metal: public material
    {
    public:
        vec3<float> albedo;

    public:
        metal();
        metal(const vec3<float> &metal_albedo);
    
    public:
        virtual bool scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> attenuation, AFei::ray<float> &r_out) const;
        virtual AFei::ray<float> reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const; 
    };
};

AFei::metal::metal()
{
    albedo = vec3<float>(0.0f, 0.0f, 0.0f);
}

AFei::metal::metal(const vec3<float> &metal_albedo)
{
    albedo = metal_albedo;
}

bool AFei::metal::scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> attenuation, AFei::ray<float> &r_out) const
{
    r_out = reflect(r_in, rec);
    attenuation = this->albedo;
    return (dot(r_out.direction, rec.normal) > 0);
}

//r_out = r_in + 2 * r_b
AFei::ray<float> AFei::metal::reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const
{
    auto r_in_temp = r_in.direction;
    r_in_temp.x = -r_in_temp.x;
    r_in_temp.y = -r_in_temp.y;
    r_in_temp.z = -r_in_temp.z;
    auto r_b = rec.normal * dot(r_in_temp, rec.normal);
    auto r_out = ray<float>(rec.intersectPoint, (r_in_temp + 2 * r_b).normal_vector());
    return r_out;
}
#endif