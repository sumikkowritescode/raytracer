#include "ray.h"

namespace Raytracer {
    Ray::Ray() {
        m_origin = Vec3f(0.0f, 0.0f, 0.0f);
        m_direction = Vec3f(0.0f, 0.0f, 0.0f);
    }

    Ray::Ray(const Vec3f &origin, const Vec3f &direction) {
        m_origin = origin;
        m_direction = direction;
    }

    void Ray::SetOrigin(const Vec3f &origin) {
        m_origin = origin;
    }

    void Ray::SetDirection(const Vec3f &direction) {
        m_direction = direction;
    }

    Vec3f Ray::GetOrigin() const {
        return m_origin;
    }

    Vec3f Ray::GetDirection() const {
        return m_direction;
    }

    Vec3f Ray::GetInverseDirection() const {
        if (m_direction.x != 0.0f || m_direction.y != 0.0f || m_direction.z != 0.0f)
            return Vec3f(
                1.0f / m_direction.x,
                1.0f / m_direction.y,
                1.0f / m_direction.z
            );
        else
            return Vec3f(0.0f, 0.0f, 0.0f);
    }
}
