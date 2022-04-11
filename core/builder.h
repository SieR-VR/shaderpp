#ifndef BUILDER_H_
#define BUILDER_H_

#include "parser.h"

#include "variable.h"
#include "function.h"
#include "struct.h"

namespace GLSL
{
    class Builder
    {
    public:
        Builder(const std::string &version)
            : glsl_version("#version " + version + " core\n")
        {
        }

        Builder(const std::string &version, const std::string &profile)
            : glsl_version("#version " + version + " " + profile + "\n")
        {
        }

        Builder &add_outputs(const std::vector<Variable> &outputs)
        {
            for (const auto &output : outputs)
                output_variables.push_back("out " + output.get_declaration() + ";\n");
            return *this;
        }

        Builder &add_inputs(const std::vector<Variable> &inputs)
        {
            for (const auto &input : inputs)
                input_variables.push_back("in " + input.get_declaration() + ";\n");
            return *this;
        }

        Builder &add_uniforms(const std::vector<Variable> &uniforms)
        {
            for (const auto &uniform : uniforms)
                uniform_variables.push_back("uniform " + uniform.get_declaration() + ";\n");
            return *this;
        }

        template <class T>
        Builder &add_struct(const StructDecl<T> &struct_decl)
        {
            struct_decls.push_back(struct_decl.declaration);
            struct_impls.push_back(struct_decl.definition);
            return *this;
        }

        template <class... Args>
        Builder &add_function(const Function<Args...> &function)
        {
            function_decls.push_back(function.declaration);
            function_impls.push_back(function.definition);
            return *this;
        }

        std::string build()
        {
            std::string result = glsl_version;
            result += "\n";

            for (const auto &output : output_variables)
                result += output;
            if (output_variables.size())
                result += "\n";

            for (const auto &input : input_variables)
                result += input;
            if (input_variables.size())
                result += "\n";

            for (const auto &struct_decl : struct_decls)
                result += struct_decl;
            if (struct_decls.size())
                result += "\n";

            for (const auto &function_decl : function_decls)
                result += function_decl;
            if (function_decls.size())
                result += "\n";

            for (const auto &uniform_variable : uniform_variables)
                result += uniform_variable;
            if (uniform_variables.size())
                result += "\n";

            for (const auto &struct_impl : struct_impls)
                result += struct_impl;
            if (struct_impls.size())
                result += "\n";

            for (const auto &function_impl : function_impls)
                result += function_impl;
            if (function_impls.size())
                result += "\n";

            result += Parser::parse_main();
            return result;
        }

    private:
        std::string glsl_version;
        std::vector<std::string> output_variables;
        std::vector<std::string> input_variables;

        std::vector<std::string> struct_decls;
        std::vector<std::string> function_decls;

        std::vector<std::string> uniform_variables;
        std::vector<std::string> struct_impls;
        std::vector<std::string> function_impls;
    };
}

#endif