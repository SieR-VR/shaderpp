#ifndef VEC4_H_
#define VEC4_H_

#include "../variable.h"

#include "float.h"
#include "vec2.h"
#include "vec3.h"

namespace GLSL
{
    class Vec4 : public Variable
    {
    public:
        Float x, y, z, w, r, g, b, a, s, t, p, q;

        Vec4() = delete;
        Vec4(const std::string &symbol);
        Vec4(const std::string &symbol, Variable* origin);
        Vec4(const Vec4 &other);
        Vec4(const Float &f1, const Float &f2, const Float &f3, const Float &f4);

        void *operator new(size_t size);
        Vec4 &operator=(const Vec4 &other);

        static std::string get_type();
    };
}

#endif