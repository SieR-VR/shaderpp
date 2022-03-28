#include <iostream>

#include "core/parser.h"
#include "core/float.h"

int main(int argc, char *argv[])
{
    using namespace GLSL;
    std::function<Float(Float &, Float &)> to_parse = [](Float &a1, Float &a2)
    {
        Float a1_sq = a1 * a1;
        return a1_sq;
    };

    std::string parsed = Parse(to_parse, "some_function");
    std::cout << parsed << std::endl;
    return 0;
}