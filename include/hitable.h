#ifndef HITABLE_H_
#define HITABLE_H_

#include "ray.hxx"

class Material;

struct hitRecord
{
    float t;
    int obNumber;
    AFei::vec3<float> intersectPoint;
    AFei::vec3<float> normal;
};

class hiTabel
{
public:
    virtual bool hit(AFei::ray<float> &r, float t_min, float t_max, hitRecord &rec) const= 0;
};

class Material
{
public:
    virtual bool scatter(const AFei::ray<float> &r_in, const hitRecord &rec, AFei::vec3<float> attenuation, AFei::ray<float> &r_out) const = 0;
};

#endif