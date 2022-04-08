#include <iostream>

#include "../core/variable.h"
#include "../core/internal_functions.h"

#include "regex/regex_builder.h"

int main() {
    using namespace GLSL;

    std::function<Float(Int &, Float &)> func = [](Int &a0, Float &a1) {
        return a1;
    };

    auto some_function = Parser::Parse(func, "some_function");

    RegexBuilder arguments_regex;
    arguments_regex.string("arg_")
                   .between({{'0', '9'}, {'a', 'f'}})
                   .count(8);

    RegexBuilder variables_regex;
    variables_regex.string("va_")
                   .between({{'0', '9'}, {'a', 'f'}})
                   .count(8);
    
    RegexBuilder function_regex;
    function_regex.string("float some_function")
                  .string("\\(")
                  .string("int").space()
                  .append(arguments_regex)
                  .string(",").space()
                  .string("float").space()
                  .append(arguments_regex)
                  .string("\\)");

    RegexBuilder declaration_regex = function_regex;
    declaration_regex.string(";\n");

    RegexBuilder definition_regex = function_regex;
    definition_regex.space().string("\\{").line_break()
                    .many({
                        RegexBuilder("\treturn ").append(arguments_regex).string(";").line_break(),
                        RegexBuilder("\t").string("float ").append(variables_regex)
                                          .string(" = ").append(arguments_regex).string(";").line_break()
                                          .string("\treturn ").append(variables_regex).string(";").line_break()
                    })
                    .string("\\}").line_break();

    if (!std::regex_match(some_function.declaration, declaration_regex.build())) {
        std::cout << "Expected: " << declaration_regex.pattern_ << std::endl;
        std::cout << "Actual: " << some_function.declaration << std::endl;

        return 1;
    }

    if (!std::regex_match(some_function.definition, definition_regex.build())) {
        std::cout << "Expected: " << definition_regex.pattern_ << std::endl;
        std::cout << "Actual: " << some_function.definition << std::endl;

        return 1;
    }

    return 0;
}