#ifndef INTERNAL_FUNCTIONS_H_
#define INTERNAL_FUNCTIONS_H_

#include "parser.h"

#include "types/float.h"
#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

#include "types/int.h"

namespace GLSL
{
    Float &sin(const Float &a);
    Float &cos(const Float &a);
    Float &tan(const Float &a);

    Float &max(const Float &a, const Float &b);
    Float &pow(const Float &a, const Float &b);

    Float &dot(const Vec2 &a, const Vec2 &b);
    Float &dot(const Vec3 &a, const Vec3 &b);

    Vec2 &normalize(const Vec2 &a);
    Vec3 &normalize(const Vec3 &a);

    Vec3 &reflect(const Vec3 &a, const Vec3 &b);
}

#endif