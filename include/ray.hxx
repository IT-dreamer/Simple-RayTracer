#ifndef RAY_HXX_
#define RAY_HXX_
#include "vec3.hxx"

namespace AFei
{
    template<class T>
    class ray
    {
    public:
        vec3<T> original;
        vec3<T> direction;

    public:
        ray();
        ray(vec3<T> rayOriginal, vec3<T> rayDirection);
    
    public:
        vec3<T> rayPostion(float t);
    };
};

template<class T>
AFei::ray<T>::ray()
{}

template<class T>
AFei::ray<T>::ray(vec3<T> rayOriginal, vec3<T> rayDirection)
{
    this->original = rayOriginal;
    this->direction = rayDirection;
}

template<class T>
AFei::vec3<T> AFei::ray<T>::rayPostion(float t)
{
    vec3<T> temp = this->original + (T)t * this->direction;
    return temp;
}

#endif