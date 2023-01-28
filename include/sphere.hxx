#ifndef SPHERE_H_
#define SPHERE_H_

#include "hitable.h"

namespace AFei
{
    class sphere:public hiTabel
    {
    public:
        vec3<float> center;
        float radius;
        material *mat_ptr;
    
    public:
        sphere();
        sphere(vec3<float> sphereCenter, float sphereRadius, material *sphere_material);
        sphere(const sphere &obj);
    
    public:
        inline void operator =(const sphere &obj);
        virtual bool hit(ray<float> &r, float t_min, float t_max, hitRecord &rec) const;
    };
}

AFei::sphere::sphere()
{
    this->center = vec3<float>(0.0f, 0.0f, 0.0f);
    this->radius = 0.0f;
    this->mat_ptr = nullptr;
}

AFei::sphere::sphere(vec3<float> sphereCenter, float sphereRadius, material *sphere_material)
{
    this->center = sphereCenter;
    this->radius = sphereRadius;
    this->mat_ptr = sphere_material;
}

AFei::sphere::sphere(const sphere &obj)
{
    this->center = obj.center;
    this->radius = obj.radius;
    this->mat_ptr = obj.mat_ptr;
}

inline void AFei::sphere::operator=(const sphere &obj)
{
    this->center = obj.center;
    this->radius = obj.radius;
    this->mat_ptr = obj.mat_ptr;
}

bool AFei::sphere::hit(ray<float> &r, float t_min, float t_max, hitRecord &rec) const
{
    float t;
    auto oc = r.original - this->center;
    auto a = dot(r.direction, r.direction);
    auto b = dot(r.direction, oc) * 2.0;
    auto c = dot(oc, oc) - this->radius * this->radius;
    auto discriminante = b * b - 4 * a * c;

    if(discriminante >= 0)
    {
        t = (-b - std::sqrt(discriminante)) / 2.0f * a;
        if(t < t_max && t > t_min)
        {
            rec.t = t;
            rec.intersectPoint = r.rayPostion(t);
            rec.normal = (rec.intersectPoint - this->center).normal_vector();
            rec.mat_ptr = this->mat_ptr;
            return true;
        }

        t = (-b + std::sqrt(discriminante)) / 2.0f * a;;
        if(t < t_max && t > t_min)
        {
            rec.t = t;
            rec.intersectPoint = r.rayPostion(t);
            rec.normal = (rec.intersectPoint - this->center).normal_vector();
            rec.mat_ptr = this->mat_ptr;
            return true;
        }
    }
    return false;
}

#endif