#include "triangle.h"

namespace Raytracer {
    Triangle::Triangle() :
        m_epsilon(static_cast<float>(1e-8))
    {
    }

    Triangle::Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2) :
        m_v0(v0),
        m_v1(v1),
        m_v2(v2),
        m_epsilon(static_cast<float>(1e-8))
    {
        m_bbox.Calculate(m_v0, m_v1, m_v2);
    }

    Triangle::Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, const Vec3f &n0, const Vec3f &n1, const Vec3f &n2) :
        m_v0(v0),
        m_v1(v1),
        m_v2(v2),
        m_n0(n0),
        m_n1(n1),
        m_n2(n2),
        m_epsilon(static_cast<float>(1e-8))
    {
        m_bbox.Calculate(m_v0, m_v1, m_v2);
    }

    void Triangle::SetVertices(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2) {
        m_v1 = v0;
        m_v1 = v1;
        m_v2 = v2;

        m_bbox.Calculate(m_v0, m_v1, m_v2);
    }


    void Triangle::SetNormals(const Vec3f &n0, const Vec3f &n1, const Vec3f &n2) {
        m_n1 = n0;
        m_n1 = n1;
        m_n2 = n2;
    }

    // Möller-Trumbore algorithm to check Ray/Triangle intersection
    bool Triangle::GetIntersection(const Ray &ray, float &t) {
        Vec3f v0v1 = m_v1 - m_v0;
        Vec3f v0v2 = m_v2 - m_v0;
        Vec3f pvec = cross(ray.GetDirection(), v0v2);
        float determinant = dot(v0v1, pvec);

        if (fabs(determinant) < m_epsilon)
            return false;

        float inverseDeterminant = 1 / determinant;

        Vec3f tvec = ray.GetOrigin() - m_v0;
        m_u = dot(tvec, pvec) * inverseDeterminant;

        if (m_u < 0 || m_u > 1)
            return false;

        Vec3f qvec = cross(tvec, v0v1);
        m_v = dot(ray.GetDirection(), qvec) * inverseDeterminant;

        if (m_v < 0 || m_u + m_v > 1)
            return false;

        t = dot(v0v2, qvec) * inverseDeterminant;

        return true;
    }

    BoundingBox Triangle::GetBoundingBox() const {
        return m_bbox;
    }

    // TODO: pre-calculate and store instead?
    Vec3f Triangle::GetMidPoint() const {
        return ( (m_v0 + m_v1 + m_v2) / 3);
    }

    Vec3f Triangle::GetNormal() const {
        Vec3f normal = m_n0 + (m_n1 - m_n0) * m_u + (m_n2 - m_n0) * m_v;
        normal.normalize();
        return normal;
    }
}
