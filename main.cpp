#include <iostream>

#include "parser.h"
#include "float.h"

int main(int argc, char *argv[])
{
    std::function<Float&(Float&, Float&)> to_parse = [](Float &a1, Float &a2) -> Float& {
        Float a1_copy = a1;
        Float a2_copy = a2 + a1_copy;
        Float result = a1_copy + a2_copy;
        return a1_copy * a1 + a2_copy * a2 + result;
    };
    
    std::string parsed = Parser::Parse(to_parse, std::string("some_function"));
    std::cout << parsed << std::endl;
    return 0;
}