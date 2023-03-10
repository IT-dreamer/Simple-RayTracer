#ifndef CAMERA_H_
#define CMAERA_H_

#include "ray.hxx"
#include "other.h"

namespace AFei
{
    class camera
    {
    public:
        vec3<float> origin;
        vec3<float> lower_left_corner;
        vec3<float> horizontal;
        vec3<float> vertical;
        vec3<float> u, v, w;
        float lens_radius;
    
    public:
        camera();
        camera(float camera_fov, float camera_aspect);
        camera(vec3<float> camera_origin, vec3<float> camera_lower_left_corner, \
        vec3<float> camera_horizontal, vec3<float> camera_vertical);
        camera(vec3<float> lookfrom, vec3<float> lookat, vec3<float> up, float vfov, \
        float aspect);
        camera(vec3<float> lookfrom, vec3<float> lookat, vec3<float> up, float vfov, \
        float aspect, float aperture, float focus_dist);
    
    public:
        ray<float> get_ray(float u, float v);
        ray<float> get_Lens_ray(float u, float v);
    };
}

AFei::camera::camera()
{
    this->origin = vec3<float>(0.0f, 0.0f, 0.0f);
    this->lower_left_corner = vec3<float>(-2.0f, -1.0f, -1.0f);
    this->horizontal = vec3<float>(4.0f, 0.0f, 0.0f);
    this->vertical = vec3<float>(0.0f, 2.0f, 0.0f);
}

AFei::camera::camera(float camera_fov, float camera_aspect)
{
    float theta  = camera_fov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0f);
    float half_width = camera_aspect * half_height;
    lower_left_corner = vec3<float>(-half_width, -half_height, -1.0f);
    horizontal = vec3<float>(2.0f * half_width, 0.0f, 0.0f);
    vertical = vec3<float>(0.0f, 2.0f * half_height, 0.0f);
    origin = vec3<float>(0.0f, 0.0f, 0.0f);
}

AFei::camera::camera(vec3<float> camera_origin, vec3<float> camera_lower_left_corner, \
    vec3<float> camera_horizontal, vec3<float> camera_vertical)
{
    this->origin = camera_origin;
    this->lower_left_corner = camera_lower_left_corner;
    this->horizontal = camera_horizontal;
    this->vertical = camera_vertical;
}

AFei::camera::camera(vec3<float> lookfrom, vec3<float> lookat, vec3<float> up, float vfov, float aspect)
{
    float theta = vfov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = (lookfrom - lookat).normal_vector();
    u = cross(up, w).normal_vector();
    v = cross(w, u);
    lower_left_corner = origin - half_width * u - half_height * v- w;
    horizontal = 2.0f * half_width * u;
    vertical = 2.0f * half_height * v;
}

AFei::camera::camera(vec3<float> lookfrom, vec3<float> lookat, vec3<float> up, float vfov, float aspect, float aperture, float focus_dist)
{
    lens_radius = aperture / 2.0f;
    float theta = vfov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = (lookfrom - lookat).normal_vector();
    u = cross(up, w).normal_vector();
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u  - half_height * focus_dist * v  - focus_dist * w;
    horizontal = 2.0f * half_width * focus_dist * u;
    vertical = 2.0f * half_height * focus_dist * v;
}

AFei::ray<float> AFei::camera::get_ray(float u, float v)
{
    auto ray_dir = lower_left_corner + u * this->horizontal + v * this->vertical - this->origin;
    ray_dir.normalization();
    return ray<float>(this->origin, ray_dir);
}

AFei::ray<float> AFei::camera::get_Lens_ray(float s, float t)
{
    vec3<float> rd = lens_radius * randomInUnitDisk();
    vec3<float> offset = this->u * rd.x + this->v * rd.y;
    auto ray_dir = lower_left_corner + s * this->horizontal + t * this->vertical - this->origin - offset;
    ray_dir.normalization();
    return ray(this->origin + offset, ray_dir);
}

#endif