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
    Float &sin(const Float &a)
    {
        Float *result = new Float("sin(" + a.get_expression() + ")"); 
        return *result;
    }

    Float &cos(const Float &a)
    {
        Float *result = new Float("cos(" + a.get_expression() + ")");
        return *result;
    }

    Float &tan(const Float &a)
    {
        Float *result = new Float("tan("  + a.get_expression() + ")");
        return *result;
    }

    Float &max(const Float &a, const Float &b)
    {
        Float *result = new Float("max(" + a.get_expression() + ", " + b.get_expression() + ")");
        return *result;
    }

    Float &pow(const Float &a, const Float &b)
    {
        Float *result = new Float("pow(" + a.get_expression() + ", " + b.get_expression() + ")");
        return *result;
    }

    Float &dot(const Vec2 &a, const Vec2 &b)
    {
        Float *result = new Float("dot(" + a.get_expression() + ", " + b.get_expression() + ")");
        return *result;
    }

    Float &dot(const Vec3 &a, const Vec3 &b)
    {
        Float *result = new Float("dot(" + a.get_expression() + ", " + b.get_expression() + ")");
        return *result;
    }

    Vec2 &normalize(const Vec2 &a)
    {
        Vec2 *result = new Vec2("normalize(" + a.get_expression() + ")");
        return *result;
    }

    Vec3 &normalize(const Vec3 &a)
    {
        Vec3 *result = new Vec3("normalize(" + a.get_expression() + ")");
        return *result;
    }

    Vec3 &reflect(const Vec3 &a, const Vec3 &b)
    {
        Vec3 *result = new Vec3("reflect(" + a.get_expression() + ", " + b.get_expression() + ")");
        return *result;
    }
}

#endif