#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <functional>

#include "namer.h"
#include "function.h"

namespace GLSL
{
    namespace Parser
    {
        static std::vector<std::string> recorder;

        static int arg_index = 0;
        static std::string argument_declaration = "";

        static void record(std::string s)
        {
            recorder.push_back("\t" + s + ";\n");
        }

        template <typename T, typename A>
        static T execute(std::function<T(A &)> func, A &arg)
        {
            argument_declaration += arg.get_declaration();
            return func(arg);
        }

        template <typename T, typename A1, typename A2, typename... Args>
        static T execute(std::function<T(A1 &, A2 &, Args &...)> func, A1 &a1)
        {
            argument_declaration += a1.get_declaration() + ", ";

            std::function<T(A2 &, Args & ...)> bound = [&](A2 &a2, Args &...others) -> T
            {
                return func(a1, a2, others...);
            };

            A2 a2(Namer::name("arg_", arg_index++, A2::get_type(), ""));
            return execute(bound, a2);
        }

        template <typename T, typename A, typename... Args>
        static Function<T, A, Args...> Parse(std::function<T(A &, Args &...)> func, std::string func_name)
        {
            recorder.clear();
            arg_index = 0;
            argument_declaration = "";

            A a(Namer::name("arg_", arg_index++, A::get_type(), ""));
            T t = execute<T, A, Args...>(func, a);

            Function<T, A, Args...> function(func_name);

            std::string header = t.glsl_type + " " + func_name + "(" + argument_declaration + ")";
            std::string footer = "}\n";

            function.definition = header + " {\n";
            for (std::string line : recorder)
                function.definition += line;
            function.definition += "\treturn " + t.get_expression() + ";\n";
            function.definition += footer;

            function.declaration = header + ";\n";

            return function;
        }
    }

    
} // namespace GLSL

#endif