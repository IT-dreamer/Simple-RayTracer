#ifndef DIELECTRIC_HXX_
#define DIELECTRIC_HXX_

#include "hitable.h"
#include "other.h"

namespace AFei
{
    class dielectirc: public material
    {
        public:
        float _ref_idx;
        vec3<float> _albedo;
    
        public:
        dielectirc();
        dielectirc(float ref_idx);

        public:
        virtual bool scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> &attenuation, AFei::ray<float> &r_out) const;
        virtual AFei::ray<float> reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const;
        bool refract(const AFei::vec3<float> &r_in_dir, const AFei::vec3<float> r_in_normal, float ni_over_nt, AFei::vec3<float> &r_out_dir) const;
        float shilick(float cosine, float ref_idx) const;
    };
}

AFei::dielectirc::dielectirc()
{
    _ref_idx = -1.0f;
    _albedo = vec3<float>(1.0f, 1.0f, 1.0f);
}

AFei::dielectirc::dielectirc(float ref_idx)
{
    _ref_idx = ref_idx;
    _albedo = vec3<float>(1.0f, 1.0f, 1.0f);
}

bool AFei::dielectirc::scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> &attenuation, AFei::ray<float> &r_out) const
{
    vec3<float> outward_normal = rec.normal;
    //auto r_in_temp = r_in;
    float ni_over_nt;
    attenuation = _albedo;
    vec3<float> refracted;
    float cosine;
    float reflect_prob;

    //光线从玻璃小球内部打入外部
    if(dot(r_in.direction, rec.normal) > 0)
    {
        ni_over_nt = _ref_idx;
        outward_normal = -outward_normal;
        cosine = dot(r_in.direction, rec.normal);
    }
    //光线从外部打入玻璃小球
    else
    {
        ni_over_nt = 1.0 / _ref_idx;
        outward_normal = rec.normal;
        cosine = -dot(r_in.direction, rec.normal);
    }

    //发生折射
    if(refract(r_in.direction, outward_normal, ni_over_nt, refracted))
    {
        reflect_prob = shilick(cosine, _ref_idx);
    }
    //发生全反射
    else
    {
        reflect_prob = 1.0f;
    }

    if(generateRandom(0.001f, 1.0f) < reflect_prob)
    {
        r_out = reflect(r_in, rec);
    }
    else
    { 
        r_out = ray<float>(rec.intersectPoint, refracted);
    }
    return true;
}

float AFei::dielectirc::shilick(float cosine, float ref_idx) const
{
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * pow((1.0f - cosine), 5);
}

AFei::ray<float> AFei::dielectirc::reflect(const AFei::ray<float> &r_in, const hitRecord &rec) const
{
    auto r_in_temp = r_in.direction;
    auto r_out_dir = r_in_temp - 2.0f * dot(r_in_temp, rec.normal) * rec.normal;
    auto r_out = ray<float>(rec.intersectPoint, r_out_dir.normal_vector());
    return r_out;
}

bool AFei::dielectirc::refract(const AFei::vec3<float> &r_in_dir, const AFei::vec3<float> r_in_normal, float ni_over_nt, AFei::vec3<float> &r_out_dir) const
{
    float cos_theta = dot(r_in_dir, r_in_normal);
    float cos_theta_prime = 1.0f - ni_over_nt * ni_over_nt * (1.0f - cos_theta * cos_theta);
    if(cos_theta_prime > 0)
    {
        auto r_in_normal_temp = r_in_normal;
        //auto r_in_dir_temp = r_in_dir;
        //r_out_dir = -r_in_normal_temp * sqrt(cos_theta_prime) + ni_over_nt * (r_in_dir_temp - r_in_normal * cos_theta);
        r_out_dir = -r_in_normal_temp * sqrt(cos_theta_prime);
        r_out_dir.normalization();
        return true;
    }
    else
    {
        return false;
    }
}

#endif