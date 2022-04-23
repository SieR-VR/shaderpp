#include "types/float.h"

namespace GLSL
{
    Float::Float(std::string expression)
        : Variable("float", expression)
    {
    }

    Float::Float(std::string token, Variable *origin)
        : Variable("float", token, origin)
    {
    }

    Float::Float(const Float &other)
        : Variable("float")
    {
        Parser::record("float " + this->get_expression() + " = " + other.get_expression());
    }

    Float::Float(float value)
        : Variable("float", std::to_string(value))
    {
    }

    void *Float::operator new(size_t size)
    {
        return Variable::operator new(size);
    }

    Float &Float::operator=(const Float &other)
    {
        Parser::record(this->get_expression() + " = " + other.get_expression());
        return *this;
    }

    Float &Float::operator+(const Float &other)
    {
        Float *result = new Float(bin_exp("+", other));
        return *result;
    }

    Float &Float::operator-(const Float &other)
    {
        Float *result = new Float(bin_exp("-", other));
        return *result;
    }

    Float &Float::operator*(const Float &other)
    {
        Float *result = new Float(bin_exp("*", other));
        return *result;
    }

    Float &Float::operator/(const Float &other)
    {
        Float *result = new Float(bin_exp("/", other));
        return *result;
    }

    std::string Float::get_type()
    {
        return "float";
    }
}