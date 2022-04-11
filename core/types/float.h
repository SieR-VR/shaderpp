#ifndef FLOAT_H_
#define FLOAT_H_

#include "../variable.h"

namespace GLSL
{
    class Float : public Variable
    {
    public:
        Float() = delete;

        Float(std::string expression)
            : Variable("float", expression)
        {
        }

        Float(std::string token, std::weak_ptr<Variable> origin)
            : Variable("float", token, origin)
        {
        }

        Float(const Float &other)
            : Variable("float")
        {
            Parser::record("float " + this->get_expression() + " = " + other.get_expression());
        }

        Float(float value)
            : Variable("float", std::to_string(value))
        {
        }

        Float &operator=(Float &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }

        Float &operator+(Float &other)
        {
            Float *result = new Float(bin_exp("+", this, &other));
            return *result;
        }

        Float &operator-(Float &other)
        {
            Float *result = new Float(bin_exp("-", this, &other));
            return *result;
        }

        Float &operator*(Float &other)
        {
            Float *result = new Float(bin_exp("*", this, &other));
            return *result;
        }

        Float &operator/(Float &other)
        {
            Float *result = new Float(bin_exp("/", this, &other));
            return *result;
        }

        static std::string get_type()
        {
            return "float";
        }
    };
}

#endif