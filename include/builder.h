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
        Builder(const std::string &version);
        Builder(const std::string &version, const std::string &profile);

        Builder &add_outputs(const std::vector<Variable> &outputs);
        Builder &add_inputs(const std::vector<Variable> &inputs);
        Builder &add_uniforms(const std::vector<Variable> &uniforms);
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

        std::string build();

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