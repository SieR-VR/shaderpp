#include <iostream>

#include "../core/parser.h"
#include "../core/internal_functions.h"

#include "test_utils.h"

int main() {
    using namespace GLSL;

    std::function<Float(Int &, Float &)> func = [](Int &a0, Float &a1) {
        return a1;
    };

    auto some_function = Parse(func, "some_function");

    if (!ASSERT_EQUAL(some_function.declaration, "float some_function(int a0, float a1);\n")) {
        std::cerr << "Expected declaration: " << "float some_function(int a0, float a1);\n"
                  << "Actual declaration: " << some_function.declaration << std::endl;
        return -1;
    }

    if (!ASSERT_EQUAL(some_function.definition,
                      "float some_function(int a0, float a1) {\n"
                      "\tfloat v0 = a1;\n"
                      "\treturn v0;\n"
                      "}\n")) {
        std::cerr << "Expected definition: " << "float some_function(int a0, float a1) {\n"
                                                 "\tfloat v0 = a1;\n"
                                                 "\treturn a1;\n"
                                                 "}\n"
                  << "Actual definition: " << some_function.definition << std::endl;
        return -1;
    }

    return 0;
}