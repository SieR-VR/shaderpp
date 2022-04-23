#ifndef VEC3_H_
#define VEC3_H_

#include "../variable.h"

#include "float.h"
#include "vec2.h"

namespace GLSL
{
    class Vec3 : public Variable
    {
    public:
        Float x, y, z, r, g, b, s, t, p;

        Vec3() = delete;
        Vec3(const std::string& symbol);
        Vec3(const std::string& symbol, Variable* origin);
        Vec3(const Vec3 &other);
        Vec3(const Float &f1, const Float &f2, const Float &f3);

        void *operator new(size_t size);
        Vec3 &operator=(const Vec3 &other);
        Vec3 &operator+(const Vec3 &other);
        Vec3 &operator-(const Vec3 &other);
        Vec3 &operator*(const Vec3 &other);
        Vec3 &operator/(const Vec3 &other);
        Vec3 &operator*(const Float &other);
        Vec3 &operator/(const Float &other);
        Vec3 &operator-();
        static std::string get_type();
    };
}

#endif