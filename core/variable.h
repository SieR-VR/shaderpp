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
        Variable * origin = nullptr;

        Variable(std::string glsl_type) 
            : glsl_type(glsl_type), 
              expression(Namer::name("va_", Parser::recorder.size(), glsl_type, ""))
        {
        }

        Variable(std::string glsl_type, std::string expression)
            : glsl_type(glsl_type), expression(expression)
        {
        }

        Variable(std::string glsl_type, std::string token, Variable* origin)
            : glsl_type(glsl_type), expression(token), origin(origin)
        {
            if (origin)
                origin->branches.push_back(this);
        }

        void *operator new(size_t size)
        {
            return Parser::allocate(size);
        }

        static std::string bin_exp(std::string token, const Variable *left, const Variable *right)
        {
            return "(" + left->get_expression() + " " + token + " " + right->get_expression() + ")";
        }

        static std::string un_exp(std::string token, Variable *right)
        {
            return "(" + token + right->get_expression() + ")";
        }

        std::string get_declaration() const
        {
            return glsl_type + " " + expression;
        }

        std::string get_expression() const
        {
            if (origin)
                return origin->get_expression() + "." + expression;
            else
                return expression;
        }
    };
}

#endif