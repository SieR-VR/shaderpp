#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <functional>

#include "namer.h"
#include "function.h"

namespace GLSL
{
    class Parser
    {
    public:
        inline static std::vector<std::string> recorder;

        inline static int arg_index = 0;
        inline static std::string argument_declaration = "";

        /**
         * @brief The function records the function line
         */
        static void record(std::string s)
        {
            recorder.push_back("\t" + s + ";\n");
        }

        /**
         * @brief The helper function executes the function
         * @tparam T The return type of the function
         * @tparam A The last argument type of the function
         * @param func The function to be executed
         * @param arg The last argument of the function
         */
        template <typename T, typename A>
        static T execute(std::function<T(A &)> func, A &arg)
        {
            argument_declaration += arg.get_declaration();
            return func(arg);
        }

        /**
         * @brief The helper function executes the function
         * @tparam T The return type of the function
         * @tparam A1 The first argument type of the function
         * @tparam A2 The second argument type of the function
         * @tparam ...Args The rest of the argument types of the function
         * @param func The function to be executed
         * @param arg The last argument of the function
         */
        template <typename T, typename A1, typename A2, typename... Args>
        static T execute(std::function<T(A1 &, A2 &, Args &...)> func, A1 &arg)
        {
            argument_declaration += arg.get_declaration() + ", ";

            std::function<T(A2 &, Args & ...)> bound = [&](A2 &a2, Args &...others) -> T
            {
                return func(arg, a2, others...);
            };

            A2 a2(Namer::name("arg_", arg_index++, A2::get_type(), ""));
            return execute(bound, a2);
        }

        /**
         * @brief The main function of the parser
         * @tparam T The return type of the function
         * @tparam ...Args Argument types of the function
         * @param func The function to be executed
         * @param func_name The name of the function
         * @return Function<T, Args> The function object
         */
        template <typename T, typename A, typename... Args>
        static Function<T, A, Args...> parse(std::function<T(A &, Args &...)> func, std::string func_name)
        {
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

            recorder.clear();
            arg_index = 0;
            argument_declaration = "";

            return function;
        }
        
        /**
         * @brief Another main function of the parser, this one is for glsl main function
         * @return std::string The function definition
         */
        static std::string parse_main()
        {
            std::string definition = "";
            std::string header = "void main()";
            std::string footer = "}\n";

            definition = header + " {\n";
            for (std::string line : recorder)
                definition += line;
            definition += footer;

            recorder.clear();

            return definition;
        }
    };

    
} // namespace GLSL

#endif