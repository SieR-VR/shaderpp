#include <iostream>

#include "parser.h"
#include "float.h"
#include "bool.h"

Float some_function(Float &a1, Bool &a2)
{
    Float a1_sq = a1 * a1;

    if (a2)
        a1_sq = a1;

    return a1_sq;
}

int main(int argc, char *argv[])
{
    std::function<Float(Float &, Bool &)> to_parse = some_function;

    std::string parsed = Parser::Parse(to_parse, std::string("some_function"));
    std::cout << parsed << std::endl;
    return 0;
}