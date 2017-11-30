#include "camera.h"

// Windows gives a hard time about this so I'm saving time by just defining it.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Raytracer {
    Camera::Camera(const Vec3f &lookFrom, const Vec3f &lookAt, const Vec3f &vUp, float vFov, float aspect) {
        float theta = vFov * M_PI / 180.0f;
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;

        m_origin = lookFrom;

        m_w = unit_vector(lookFrom - lookAt);
        m_u = unit_vector(cross(vUp, m_w));
        m_v = cross(m_w, m_u);

        m_lowerLeftCorner = Vec3f(-halfWidth, -halfHeight, -1.0f);
        m_lowerLeftCorner = m_origin - halfWidth * m_u - halfHeight * m_v - m_w;

        m_horizontal = 2 * halfWidth * m_u;
        m_vertical = 2 * halfHeight * m_v;
    }

    Ray Camera::GetRay(float s, float t) {
        return Ray(m_origin, m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin);
    }
}
