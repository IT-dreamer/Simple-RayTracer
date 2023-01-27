#ifndef HITABLELISTXX_H_
#define HITABLELISTXX_H_

#include "hitable.h"

namespace AFei
{
    class hitableList:public hiTabel
    {
    public:
        int size;
        hiTabel **list;
    
    public:
        hitableList();
        hitableList(int hitableList_size, hiTabel **hitableList_list);
        virtual bool hit(ray<float> &r, float t_min, float t_max, hitRecord &rec) const;
    };
}

AFei::hitableList::hitableList()
{
    this->size = 0;
    this->list = nullptr;
}

AFei::hitableList::hitableList(int hitableList_size, hiTabel **hitableList_list)
{
    this->size = hitableList_size;
    this->list = hitableList_list;
}

bool AFei::hitableList::hit(ray<float> &r, float t_min, float t_max, hitRecord &rec) const
{
    hitRecord rec_temp;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for(int i = 0; i < this->size; i++)
    {
        if(this->list[i]->hit(r, t_min, closest_so_far, rec_temp))
        {
            hit_anything = true;
            closest_so_far = rec_temp.t;
            rec = rec_temp;
            rec.obNumber = i;
        }
    }
    return hit_anything;
}

#endif