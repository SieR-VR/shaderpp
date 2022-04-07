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
        Float *result = new Float("sin(" + a.get_expression() + ")"); 
        return *result;
    }

    Float &cos(Float &a)
    {
        Float *result = new Float("cos" + a.get_expression() + ")");
        return *result;
    }

    Float &tan(Float &a)
    {
        Float *result = new Float("tan"  + a.get_expression() + ")");
        return *result;
    }
}

#endif