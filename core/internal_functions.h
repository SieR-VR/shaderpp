#ifndef INTERNAL_FUNCTIONS_H_
#define INTERNAL_FUNCTIONS_H_

#include "parser.h"

#include "types/float.h"
#include "types/vec2.h"
#include "types/int.h"

namespace GLSL
{
    Float &sin(Float &a)
    {
        Float *result = new Float("sin", ParentType::Function, {a.tree});
        return *result;
    }

    Float &cos(Float &a)
    {
        Float *result = new Float("cos", ParentType::Function, {a.tree});
        return *result;
    }

    Float &tan(Float &a)
    {
        Float *result = new Float("tan", ParentType::Function, {a.tree});
        return *result;
    }
}

#endif