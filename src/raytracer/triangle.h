#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.hpp"
#include "ray.h"
#include "bbox.h"

namespace Raytracer {
    class Triangle {
    public:
        Triangle();
        Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2);
        Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, const Vec3f &n0, const Vec3f &n1, const Vec3f &n2);

        void SetVertices(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2);
        void SetNormals(const Vec3f &n0, const Vec3f &n1, const Vec3f &n2);

        bool GetIntersection(const Ray &ray, float &t);

        BoundingBox GetBoundingBox();

        Vec3f GetMidPoint();
        Vec3f GetNormal() const;

    private:
        BoundingBox m_bbox;

        Vec3f m_v0, m_v1, m_v2;
        Vec3f m_n0, m_n1, m_n2;
        float m_u, m_v;

        float m_epsilon;
    };
}
#endif // !TRIANGLE_H
