#include <fstream>
#include <iostream>
#include <cfloat>
#include <random>
#include "../include/ray.hxx"
#include "../include/vec3.hxx"
#include "../include/camera.hxx"
#include "../include/sphere.hxx"
#include "../include/lambertian.hxx"
#include "../include/metal.hxx"
#include "../include/dielectric.hxx"
#include "../include/hitableList.hxx"
#include "../include/other.h"

using AFei::vec3;
using AFei::ray;
using AFei::sphere;
using AFei::hitableList;
using AFei::camera;
using AFei::lambertian;
using AFei::metal;
using AFei::dielectirc;

template<class T>
vec3<float> color(ray<T> &r, hitableList *l, int depth)
{
    hitRecord rec;
    if(l->hit(r, 0.001f, FLT_MAX, rec))
    {
        ray<float> scattered;
        vec3<float> attenuation;
        if(depth < 16 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, l, depth + 1);
        }
        else
        {
            return vec3<float>(0.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        float t = 0.5f * r.direction.y + 1.0f;
        return vec3<float>(1.0f, 1.0f, 1.0f) * (1.0f - t) + vec3<float>(0.5f, 0.7f, 1.0f) * t;
    }
}

void progressBar(int quantity, int total_amount)
{
    static char buffer[101] = {0};
    static char arr[5] = {"-/|\\"};
    static float total_progress = 0.0f;
    static int i = 0;
    float current_progress = (float)quantity / (float)total_amount;

    if(current_progress > total_progress)
    {
        buffer[i] = '#';
        fprintf(stdout, "[%-100s][%d%%][%c]\r",buffer,i,arr[i%4]);
        fflush(stdout);
        total_progress += 0.01f;
        i += 1;
    }
}

int main(void)
{
    std::ofstream outFile;
    outFile.open("../target/out.ppm", std::ios::out | std::ios::trunc);
    int heigth = 400;
    int width = 800;

    outFile << "P3" << std::endl;
    outFile << width << " " << heigth << std::endl;
    outFile << "255" << std::endl;

    vec3<float> horizontal(4.0, 0.0, 0.0);  //水平向量
    vec3<float> vertical(0.0, 2.0, 0.0);    //垂直向量
    vec3<float> lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3<float> origin(0.0, 0.0, 0.0);

    camera cam(origin, lowerLeftCorner, horizontal, vertical);

    hiTabel *list[4];
    list[0] = new sphere(vec3<float>(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3<float>(0.8f, 0.3f, 0.3f)));
    list[1] = new sphere(vec3<float>(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3<float>(0.8f, 0.8f, 0.0f)));
    list[2] = new sphere(vec3<float>(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3<float>(0.8f, 0.6f, 0.2f), 0.9f));
    list[3] = new sphere(vec3<float>(-1.0f, 0.0f, -1.0f), 0.5f, new dielectirc(1.5f));
    hitableList *world = new hitableList(4, list);

    int ns = 100;

    for(int i = heigth - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            vec3<float> clr(0.0f, 0.0f, 0.0f);

            for(int k = 0; k < ns; k++)
            {
                float u = float(j + generateRandom(0.0f, 1.0f)) / (float)width;
                float v = float(i + generateRandom(0.0f, 1.0f)) / (float)heigth;
                auto myRay = cam.get_ray(u, v);
                clr += color(myRay, world, 0);               
            }               

            clr /= (float)ns;
            clr = vec3<float>((float)sqrt(clr.x), (float)sqrt(clr.y), (float)sqrt(clr.z));
            int ir = int(255.99 * clr.x);
            int ig = int(255.99 * clr.y);
            int ib = int(255.99 * clr.z);
            outFile << ir << " " << ig << " " << ib << std::endl;
        }
        progressBar(heigth - i, heigth);
    }

    outFile.close();
    std::cout << std::endl;
    return EXIT_SUCCESS;
}