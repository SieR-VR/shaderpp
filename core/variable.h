#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include <vector>
#include <memory>

#include "parser.h"

namespace GLSL
{
    class Variable : std::enable_shared_from_this<Variable>
    {
    public:
        std::string expression;
        std::string glsl_type;

        std::vector<std::shared_ptr<Variable>> branches;
        std::weak_ptr<Variable> origin;

        Variable(std::string glsl_type) 
            : glsl_type(glsl_type), 
              expression(Namer::name("va_", Parser::recorder.size(), glsl_type, ""))
        {
        }

        Variable(std::string glsl_type, std::string expression)
            : glsl_type(glsl_type), expression(expression)
        {
        }

        Variable(std::string glsl_type, std::string token, std::weak_ptr<Variable> origin)
            : glsl_type(glsl_type), expression(token), origin(origin)
        {
            if (origin.lock())
                origin.lock()->branches.push_back(shared_from_this());
        }

        static std::string bin_exp(std::string token, Variable *left, Variable *right)
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
            if (origin.lock())
                return origin.lock()->get_expression() + "." + expression;
            else
                return expression;
        }

        std::weak_ptr<Variable> This()
        {
            return weak_from_this();
        }
    };
}

#endif