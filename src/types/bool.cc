#include "types/bool.h"

namespace GLSL
{
    Bool::Bool(std::string expression)
        : Variable("bool", expression)
    {
    }

    Bool::Bool(std::string token, Variable *origin)
        : Variable("bool", token, origin)
    {
    }

    Bool::Bool(const Bool &other)
        : Variable("bool")
    {
        Parser::record("bool " + this->get_expression() + " = " + other.get_expression());
    }

    Bool::Bool(bool value)
        : Variable("bool", std::to_string(value))
    {
    }

    void *Bool::operator new(size_t size)
    {
        return Variable::operator new(size);
    }

    Bool &Bool::operator=(const Bool &other)
    {
        Parser::record(this->get_expression() + " = " + other.get_expression());
        return *this;
    }

    Bool &Bool::operator!()
    {
        Bool *result = new Bool("(!" + this->get_expression() + ")");
        return *result;
    }

    Bool &Bool::operator&&(const Bool &other)
    {
        Bool *result = new Bool("(" + this->get_expression() + " && " + other.get_expression() + ")");
        return *result;
    }

    Bool &Bool::operator||(const Bool &other)
    {
        Bool *result = new Bool("(" + this->get_expression() + " || " + other.get_expression() + ")");
        return *result;
    }

    Bool::operator bool()
    {

    }
    
    std::string get_type()
    {
        return "bool";
    }
}