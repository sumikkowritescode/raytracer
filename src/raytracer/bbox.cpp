#include "bbox.h"
#include <algorithm>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

namespace Raytracer {
    BoundingBox::BoundingBox() :
        m_min(Vec3f(0.0f, 0.0f, 0.0f)),
        m_max(Vec3f(0.0f, 0.0f, 0.0f))
    {}

    BoundingBox::BoundingBox(const Vec3f &min, const Vec3f &max) {
        m_min = min;
        m_max = max;
    }

    BoundingBox BoundingBox::Expand(const BoundingBox &other) {
        if (other.m_min.x < m_min.x)
            m_min.x = other.m_min.x;
        if (other.m_max.x > m_max.x)
            m_max.x = other.m_max.x;

        if (other.m_min.y < m_min.y)
            m_min.y = other.m_min.y;
        if (other.m_max.y > m_max.y)
            m_max.y = other.m_max.y;

        if (other.m_min.z < m_min.z)
            m_min.z = other.m_min.z;
        if (other.m_max.z > m_max.z)
            m_max.z = other.m_max.z;

        return *this;
    }

    void BoundingBox::Calculate(const std::vector<Vec3f> &vertices) {
        float min_x, min_y, min_z, max_x, max_y, max_z;

        min_x = max_x = vertices[0].x;
        min_y = max_y = vertices[0].y;
        min_z = max_z = vertices[0].z;

        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i].x < min_x)
                min_x = vertices[i].x;
            if (vertices[i].x > max_x)
                max_x = vertices[i].x;

            if (vertices[i].y < min_y)
                min_y = vertices[i].y;
            if (vertices[i].y > max_y)
                max_y = vertices[i].y;

            if (vertices[i].z < min_z)
                min_z = vertices[i].z;
            if (vertices[i].z > max_z)
                max_z = vertices[i].z;
        }

        m_min = Vec3f(min_x, min_y, min_z);
        m_max = Vec3f(max_x, max_y, max_z);
    }

    void BoundingBox::Calculate(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2) {
        std::vector<Vec3f> vertices;
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);

        Calculate(vertices);
    }

    // Uses a basic slab method to check ray intersections
    bool BoundingBox::GetIntersection(const Ray &ray) {
        double tx1 = (m_min.x - ray.GetOrigin().x) * ray.GetInverseDirection().x;
        double tx2 = (m_max.x - ray.GetOrigin().x) * ray.GetInverseDirection().x;

        double tmin = min(tx1, tx2);
        double tmax = max(tx1, tx2);

        double ty1 = (m_min.y - ray.GetOrigin().y) * ray.GetInverseDirection().y;
        double ty2 = (m_max.y - ray.GetOrigin().y) * ray.GetInverseDirection().y;

        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));

        return tmax > max(tmin, 0.0f);
    }

    int BoundingBox::GetLongestAxis() {
        float dx = m_max.x - m_min.x;
        float dy = m_max.y - m_min.y;
        float dz = m_max.z - m_min.z;

        if (dx > dy && dx > dz)
            return 0;
        else if (dy > dx && dy > dz)
            return 1;
        else if (dz > dx && dz > dy)
            return 2;
        else
            return -1;
    }
}
