#include "types/int.h"

namespace GLSL
{
    Int::Int(std::string expression)
        : Variable("int", expression)
    {
    }

    Int::Int(std::string name, Variable* origin)
        : Variable("int", name, origin)
    {
    }

    Int::Int(const Int &other)
        : Variable("int")
    {
        Parser::record("int " + this->get_expression() + " = " + other.get_expression());
    }

    void *Int::operator new(size_t size)
    {
        return Variable::operator new(size);
    }

    Int &Int::operator=(const Int &other)
    {
        Parser::record(this->get_expression() + " = " + other.get_expression());
        return *this;
    }

    std::string Int::get_type()
    {
        return "int";
    }   
}