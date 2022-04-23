#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include <vector>
#include <memory>

#include "parser.h"

namespace GLSL
{
    class Variable
    {
    public:
        std::string expression;
        std::string glsl_type;

        std::vector<Variable *> branches;
        Variable *origin = nullptr;

        Variable(std::string glsl_type);
        Variable(std::string glsl_type, std::string expression);
        Variable(std::string glsl_type, std::string token, Variable *origin);

        void *operator new(size_t size);

        std::string bin_exp(std::string token, const Variable &right) const;
        std::string un_exp(std::string token) const;

        std::string get_declaration() const;
        std::string get_expression() const;
    };
}

#endif