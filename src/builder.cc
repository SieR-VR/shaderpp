#include "builder.h"

namespace GLSL
{
    Builder::Builder(const std::string &version)
        : glsl_version("#version " + version + " core\n")
    {
    }

    Builder::Builder(const std::string &version, const std::string &profile)
        : glsl_version("#version " + version + " " + profile + "\n")
    {
    }

    Builder &Builder::add_outputs(const std::vector<Variable> &outputs)
    {
        for (const auto &output : outputs)
            output_variables.push_back("out " + output.get_declaration() + ";\n");
        return *this;
    }

    Builder &Builder::add_inputs(const std::vector<Variable> &inputs)
    {
        for (const auto &input : inputs)
            input_variables.push_back("in " + input.get_declaration() + ";\n");
        return *this;
    }

    Builder &Builder::add_uniforms(const std::vector<Variable> &uniforms)
    {
        for (const auto &uniform : uniforms)
            uniform_variables.push_back("uniform " + uniform.get_declaration() + ";\n");
        return *this;
    }

    std::string Builder::build()
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
}