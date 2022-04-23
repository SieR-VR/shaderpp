#include "variable.h"

namespace GLSL
{
    Variable::Variable(const std::string glsl_type)
        : glsl_type(glsl_type),
          expression(Namer::name("va_", Parser::recorder.size(), glsl_type, ""))
    {
    }

    Variable::Variable(const std::string glsl_type, const std::string expression)
        : glsl_type(glsl_type), expression(expression)
    {
    }

    Variable::Variable(const std::string glsl_type, const std::string token, Variable *origin)
        : glsl_type(glsl_type), expression(token), origin(origin)
    {
        if (origin)
            origin->branches.push_back(this);
    }

    void *Variable::operator new(size_t size)
    {
        return Parser::allocate(size);
    }

    std::string Variable::bin_exp(const std::string token, const Variable &right) const
    {
        return "(" + this->get_expression() + " " + token + " " + right.get_expression() + ")";
    }

    std::string Variable::un_exp(const std::string token) const
    {
        return "(" + token + this->get_expression() + ")";
    }

    std::string Variable::get_declaration() const
    {
        return glsl_type + " " + expression;
    }

    std::string Variable::get_expression() const
    {
        if (origin)
            return origin->get_expression() + "." + expression;
        else
            return expression;
    }
}