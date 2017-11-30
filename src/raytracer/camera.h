#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

namespace Raytracer {
    class Camera {
    public:
        Camera(const Vec3f &lookfrom, const Vec3f &lookat, const Vec3f &vup, float vfov, float aspect);
        Ray GetRay(float s, float t);

    private:
        Vec3f m_origin;
        Vec3f m_lowerLeftCorner;
        Vec3f m_horizontal;
        Vec3f m_vertical;

        Vec3f m_u, m_v, m_w;
    };
}

#endif // !CAMERA_H