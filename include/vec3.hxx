#ifndef VEC3_HXX_
#define VEC3_HXX_

#include <cmath>

namespace AFei
{
    template <class T>
    class vec3
    {
    public:
        T x;
        T y;
        T z;
    public:
        vec3();
        vec3(T vec3_x, T vec3_y, T vec3_z);
        vec3(const vec3<T> &obj);

    public:
        inline vec3<T> operator +(const vec3<T> &obj) const;
        inline vec3<T> operator +(const T n);
        inline vec3<T>& operator +=(const T n);
        inline vec3<T>& operator +=(const vec3<T> &obj);
        friend inline vec3<T> operator +(const T n, vec3<T> &obj)
        {
            return obj + n;
        }

        inline vec3<T> operator -(const vec3<T> &obj);
        inline vec3<T> operator -(const T n);
        inline vec3<T>& operator -=(const T n);
        inline vec3<T>& operator -=(const vec3<T> &obj);

        inline vec3<T> operator *(const vec3<T> &obj);
        inline vec3<T>& operator *=(const vec3<T> &obj);
        inline vec3<T> operator *(const T n) const;
        friend inline vec3<T> operator *(T n, vec3<T> obj)
        {
            return obj * n;
        }
        inline vec3<T>& operator *=(const T n);
        friend inline vec3<T>& operator *=(const T n, vec3<T> &obj)
        {
            obj = obj * n;
            return obj;
        }

        inline vec3<T> operator /(const vec3<T> &obj);
        inline vec3<T>& operator /=(const vec3<T> &obj);
        inline vec3<T> operator /(const T n);
        inline vec3<T>& operator /=(const T n);

        inline float length();
        inline float squaredLength() const;
        inline void normalization();
        inline vec3<T> normal_vector();
    };
}

template<class T>
AFei::vec3<T>::vec3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template<class T> 
AFei::vec3<T>::vec3(T vec3_x, T vec3_y, T vec3_z)
{
    this->x = vec3_x;
    this->y = vec3_y;
    this->z = vec3_z;
}

template<class T>
AFei::vec3<T>::vec3(const vec3<T> &obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator+(const vec3<T> &obj) const
{
    vec3<T> temp(this->x + obj.x, this->y + obj.y, this->z + obj.z);
    return temp;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator+(const T n)
{
    return vec3<T>(this->x + n, this->y + n, this->z + n);
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator+=(const T n)
{
    this->x += n;
    this->y += n;
    this->z += n;
    return *this;
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator+=(const vec3<T> &obj)
{
    this->x = (T)this->x + obj.x;
    this->y = (T)this->y + obj.y;
    this->z = (T)this->z + obj.z;
    return *this;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator-(const vec3<T> &obj)
{
    vec3<T> temp(this->x - obj.x, this->y - obj.y, this->z - obj.z);
    return temp;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator-(const T n)
{
    return vec3<T>(this->x - n, this->y - n, this->z - n);
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator-=(const vec3<T> &obj)
{
    this->x = (T)this->x - obj.x;
    this->y = (T)this->y - obj.y;
    this->z = (T)this->z - obj.z;
    return *this;    
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator-=(const T n)
{
    *this = *this - n;
    return *this;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator*(const vec3<T> &obj)
{
    vec3<T> temp(this->x * obj.x, this->y * obj.y, this->z * obj.z);
    return temp;
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator*=(const vec3<T> &obj)
{
    this->x = (T)this->x * obj.x;
    this->y = (T)this->y * obj.y;
    this->z = (T)this->z * obj.z;
    return *this;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator*(const T n) const
{
    vec3<T> temp(n * this->x, n * this->y, n * this->z);
    return temp;
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator*=(const T n)
{
    this->x = (T)n * this->x;
    this->y = (T)n * this->y;
    this->z = (T)n * this->z;
    return *this;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator/(const vec3<T> &obj)
{
    vec3<T> temp(this->x / obj.x, this->y / obj.y, this->z / obj.z);
    return temp;
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator/=(const vec3<T> &obj)
{
    this->x = (T)this->x / obj.x;
    this->y = (T)this->y / obj.y;
    this->z = (T)this->z / obj.z;
    return *this;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::operator/(const T n)
{
    vec3<T> temp((T)(this->x / n), (T)(this->y / n), (T)(this->z / n));
    return temp;
}

template<class T>
inline AFei::vec3<T>& AFei::vec3<T>::operator/=(const T n)
{
    this->x = (T)this->x / n;
    this->y = (T)this->y / n;
    this->z = (T)this->z / n;
    return *this;    
}

template<class T>
inline float AFei::vec3<T>::length()
{
    float temp = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return temp;
}

template<class T>
inline float AFei::vec3<T>::squaredLength() const
{
    float temp = this->x * this->x + this->y * this->y + this->z * this->z;
    return temp;
}

template<class T>
inline void AFei::vec3<T>::normalization()
{
    float temp = this->length();
    *this /= temp;
}

template<class T>
inline AFei::vec3<T> AFei::vec3<T>::normal_vector()
{
    vec3<T> temp = this->operator/(this->length());
    return temp;
}

template<class T>
inline float dot(const AFei::vec3<T> &v1, const AFei::vec3<T> &v2)
{
    return (float)v1.x * (float)v2.x + (float)v1.y * (float)v2.y + (float)v1.z * (float)v2.z;
}

template<class T>
inline AFei::vec3<T> cross(const AFei::vec3<T> &v1, const AFei::vec3<T> &v2)
{
    return AFei::vec3<T>((T)(v1.y * v2.z - v1.z * v2.y), (T)(-(v1.x * v2.z - v1.z * v2.x)), (T)(v1.x * v2.y - v1.y * v2.x));
}

#endif