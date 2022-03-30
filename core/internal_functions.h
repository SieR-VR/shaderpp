#ifndef INTERNAL_FUNCTIONS_H_
#define INTERNAL_FUNCTIONS_H_

#include "parser.h"

#include "types/float.h"
#include "types/vec2.h"

namespace GLSL
{
    template <typename T>
    T &sin(T &a)
    {
        T *result = new T("sin", ParentType::Function, {a.tree});
        return *result;
    }

    template <typename T>
    T &cos(T &a)
    {
        T *result = new T("cos", ParentType::Function, {a.tree});
        return *result;
    }

    template <typename T>
    T &tan(T &a)
    {
        T *result = new T("tan", ParentType::Function, {a.tree});
        return *result;
    }
}

#endif