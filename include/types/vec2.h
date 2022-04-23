#ifndef VEC2_H_
#define VEC2_H_

#include "../variable.h"
#include "float.h"

namespace GLSL
{
    class Vec2 : public Variable
    {
    public:
        Float x, y, r, g, s, t;

        Vec2() = delete;
        Vec2(const std::string& symbol);
        Vec2(const std::string& symbol, Variable* origin);
        Vec2(const Vec2 &other);
        Vec2(const Float &f1, const Float &f2);

        void *operator new(size_t size);
        Vec2 &operator=(const Vec2 &other);
        Vec2 &operator+(const Vec2 &other) const;
        Vec2 &operator-(const Vec2 &other) const;
        Vec2 &operator*(const Vec2 &other) const;
        Vec2 &operator/(const Vec2 &other) const;

        Vec2 &operator*(const Float &other) const;
        Vec2 &operator/(const Float &other) const;

        static std::string get_type();
    };
}

#endif