#ifndef BBOX_H
#define BBOX_H

#include <vector>
#include "ray.h"
#include "bbox.h"

namespace Raytracer {
    class BoundingBox {
    public:
        BoundingBox();
        BoundingBox(const Vec3f &min, const Vec3f &max);

        BoundingBox Expand(const BoundingBox &other);

        void Calculate(const std::vector<Vec3f> &vertices);
        void Calculate(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2);

        bool GetIntersection(const Ray &r);
        int GetLongestAxis();

    private:
        Vec3f m_min, m_max;
    };
}
#endif // !BBOX_H
