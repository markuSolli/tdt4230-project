#pragma once

#include <memory>
#include <vector>

#include "hittable.h"
#include "ray.h"
#include "interval.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
  public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList();

    HittableList(shared_ptr<Hittable> object);

    void clear();

    void add(shared_ptr<Hittable> object);
    
    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;
};
