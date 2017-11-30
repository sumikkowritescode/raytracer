#ifndef RAY_H
#define RAY_H
#include "vec3.hpp"

namespace Raytracer {
    class Ray {
    public:
        Ray();
        Ray(const Vec3f &origin, const Vec3f &direction);

        void SetOrigin(const Vec3f &origin);
        void SetDirection(const Vec3f &direction);

        Vec3f GetOrigin() const;
        Vec3f GetDirection() const;
        Vec3f GetInverseDirection() const;

    private:
        Vec3f m_origin, m_direction;
    };
}
#endif // !RAY_H
