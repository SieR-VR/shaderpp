#include <iostream>

#include "core/parser.h"
#include "core/internal_functions.h"

int main(int argc, char *argv[])
{
    using namespace GLSL;
    std::function<Float(Float &, Float &)> to_parse = [](Float &a1, Float &a2)
    {
        Float a1_sin = sin(a1) * cos(a2);
        return a1_sin;
    };
    auto some_function = Parse(to_parse, "some_function");

    std::function<Float(Float &, Float &)> two_parse = [&](Float &a1, Float &a2)
    {
        return some_function(a1, a2) * a2;
    };
    auto some_function2 = Parse(two_parse, "some_function2");

    std::cout << some_function.declaration
              << some_function2.declaration
              << std::endl
              << some_function.definition
              << some_function2.definition;
    return 0;
}