#ifndef INT_H_
#define INT_H_

#include "../variable.h"

namespace GLSL
{
    class Int : public Variable
    {
    public:
        Int() = delete;

        Int(std::string expression)
            : Variable("int", expression)
        {
        }

        Int(std::string name, std::weak_ptr<Variable> origin)
            : Variable("int", name, origin)
        {
        }

        Int(const Int &other)
            : Variable("int")
        {
            Parser::record("int" + this->get_expression() + " = " + other.get_expression());
        }

        Int &operator=(const Int &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }

        static std::string get_type()
        {
            return "int";
        }
    };
}

#endif