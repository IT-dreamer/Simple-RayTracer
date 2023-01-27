#ifndef CAMERA_H_
#define CMAERA_H_

#include "ray.hxx"

namespace AFei
{
    class camera
    {
    public:
        vec3<float> origin;
        vec3<float> lower_left_corner;
        vec3<float> horizontal;
        vec3<float> vertical;
    
    public:
        camera();
        camera(vec3<float> camera_origin, vec3<float> camera_lower_left_corner, \
        vec3<float> camera_horizontal, vec3<float> camera_vertical);
    
    public:
        ray<float> get_ray(float u, float v);
    };
}

AFei::camera::camera()
{
    this->origin = vec3<float>(0.0f, 0.0f, 0.0f);
    this->lower_left_corner = vec3<float>(-2.0f, -1.0f, -1.0f);
    this->horizontal = vec3<float>(4.0f, 0.0f, 0.0f);
    this->vertical = vec3<float>(0.0f, 2.0f, 0.0f);
}

AFei::camera::camera(vec3<float> camera_origin, vec3<float> camera_lower_left_corner, \
    vec3<float> camera_horizontal, vec3<float> camera_vertical)
{
    this->origin = camera_origin;
    this->lower_left_corner = camera_lower_left_corner;
    this->horizontal = camera_horizontal;
    this->vertical = camera_vertical;
}

AFei::ray<float> AFei::camera::get_ray(float u, float v)
{
    auto ray_dir = lower_left_corner + u * this->horizontal + v * this->vertical - this->origin;
    ray_dir.normalization();
    return ray<float>(this->origin, ray_dir);
}



#endif