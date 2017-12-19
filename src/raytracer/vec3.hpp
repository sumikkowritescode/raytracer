#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace Raytracer {
    class Vec3f {

    public:
        Vec3f() {}
        Vec3f(float e0, float e1, float e2) { x = e0; y = e1; z = e2; }

        inline const Vec3f& operator+() const { return *this; }
        inline Vec3f operator-() const { return Vec3f(-x, -y, -z); }

        inline Vec3f& operator+=(const Vec3f &v2);
        inline Vec3f& operator-=(const Vec3f &v2);
        inline Vec3f& operator*=(const Vec3f &v2);
        inline Vec3f& operator/=(const Vec3f &v2);
        inline Vec3f& operator*=(const float t);
        inline Vec3f& operator/=(const float t);

        inline float length() const {
            return sqrt(x * x + y * y + z * z);
        }

        inline float squared_length() const {
            return x * x + y * y + z * z;
        }

        inline void normalize() {
            float l = length();
            x = x / l;
            y = y / l;
            z = z / l;
        }

        float x, y, z;
    };

    inline std::istream& operator>>(std::istream &is, Vec3f &t) {
        is >> t.x >> t.y >> t.z;
        return is;
    }

    inline std::ostream& operator<<(std::ostream &os, const Vec3f &t) {
        os << t.x << " " << t.y << " " << t.z;
        return os;
    }

    inline Vec3f operator+(const Vec3f &v1, const Vec3f &v2) {
        return Vec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    inline Vec3f operator-(const Vec3f &v1, const Vec3f &v2) {
        return Vec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    inline Vec3f operator*(const Vec3f &v1, const Vec3f &v2) {
        return Vec3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    inline Vec3f operator/(const Vec3f &v1, const Vec3f &v2) {
        return Vec3f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    }

    inline Vec3f operator*(float t, const Vec3f &v) {
        return Vec3f(t*v.x, t*v.y, t*v.z);
    }

    inline Vec3f operator/(Vec3f v, float t) {
        return Vec3f(v.x / t, v.y / t, v.z / t);
    }

    inline Vec3f operator*(const Vec3f &v, float t) {
        return Vec3f(t*v.x, t*v.y, t*v.z);
    }

    inline float dot(const Vec3f &v1, const Vec3f &v2) {
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    inline Vec3f cross(const Vec3f &v1, const Vec3f &v2) {
        return Vec3f((v1.y*v2.z - v1.z*v2.y),
            (-(v1.x*v2.z - v1.z*v2.x)),
            (v1.x*v2.y - v1.y*v2.x)
        );
    }

    inline Vec3f& Vec3f::operator+=(const Vec3f &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vec3f& Vec3f::operator*=(const Vec3f &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    inline Vec3f& Vec3f::operator/=(const Vec3f &v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    inline Vec3f& Vec3f::operator-=(const Vec3f &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    inline Vec3f& Vec3f::operator*=(const float t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    inline Vec3f& Vec3f::operator/=(const float t) {
        float k = 1.0f / t;
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    inline Vec3f unit_vector(Vec3f v) {
        return v / v.length();
    }
}
#endif // !VEC3_H
