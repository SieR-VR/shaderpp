#ifndef BOOL_H_
#define BOOL_H_

#include "../variable.h"

namespace GLSL
{
    class Bool : public Variable
    {
    public:
        Bool() = delete;

        Bool(std::string expression)
            : Variable("bool", expression)
        {
        }

        Bool(std::string token, Variable *origin)
            : Variable("bool", token, origin)
        {
        }

        Bool(Bool &other)
            : Variable("bool")
        {
            Parser::record("bool" + this->get_expression() + " = " + other.get_expression());
        }

        Bool &operator=(Bool &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }

        Bool &operator!()
        {
            Bool *result = new Bool("(!" + this->get_expression() + ")");
            return *result;
        }

        Bool &operator&&(Bool &other)
        {
            Bool *result = new Bool("(" + this->get_expression() + " && " + other.get_expression() + ")");
            return *result;
        }

        Bool &operator||(Bool &other)
        {
            Bool *result = new Bool("(" + this->get_expression() + " || " + other.get_expression() + ")");
            return *result;
        }

        operator bool()
        {

        }

        static std::string get_type()
        {
            return "bool";
        }
    };
}

#endif