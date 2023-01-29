#ifndef METAL_HXX_
#define METAL_HXX_

#include "hitable.h"
#include "other.h"

namespace AFei
{
    class metal: public material
    {
    public:
        vec3<float> albedo;
        float f;    //模糊偏移参数

    public:
        metal();
        metal(const vec3<float> &metal_albedo);
        metal(const vec3<float> &metal_albedo, const float metal_f);
    
    public:
        virtual bool scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> &attenuation, AFei::ray<float> &r_out) const;
        virtual AFei::ray<float> reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const; 
    };
};

AFei::metal::metal()
{
    albedo = vec3<float>(0.0f, 0.0f, 0.0f);
    f = 0.0f;
}

AFei::metal::metal(const vec3<float> &metal_albedo)
{
    albedo = metal_albedo;
    f = 0.0f;
}

AFei::metal::metal(const vec3<float> &metal_albedo, const float metal_f)
{
    albedo = metal_albedo;
    metal_f > 1.0f ? this->f = 1.0f : this->f = metal_f;
}

bool AFei::metal::scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> &attenuation, AFei::ray<float> &r_out) const
{
    r_out = reflect(r_in, rec);
    attenuation = this->albedo;
    return (dot(r_out.direction, rec.normal) > 0);
}

//r_out = r_in + 2 * r_b
AFei::ray<float> AFei::metal::reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const
{
    auto r_in_temp = r_in.direction;
    auto r_out_dir = r_in_temp - 2.0f * dot(r_in_temp, rec.normal) * rec.normal;
    auto r_out = ray<float>(rec.intersectPoint, r_out_dir.normal_vector());
    if(f > 0.0f)
    {
        r_out.direction = r_out.direction + randomInUnitSphere() * this->f;
        r_out.direction.normalization();
        return r_out;
    }
    else
    {
        return r_out;
    }
}
#endif