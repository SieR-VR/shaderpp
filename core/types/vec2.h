#ifndef VEC2_H_
#define VEC2_H_

#include "../variable.h"

#include "float.h"

namespace GLSL
{
    class Vec2 : public Variable
    {
    public:
        Float x, y, r, g, s, t;

        Vec2() = delete;

        Vec2(std::string symbol)
            : Variable("vec2", symbol),
              x("x", This()), y("y", This()),
              r("r", This()), g("g", This()),
              s("s", This()), t("t", This())
        {
        }

        Vec2(std::string symbol, std::shared_ptr<Variable> origin)
            : Variable("vec2", symbol, origin),
              x("x", This()), y("y", This()),
              r("r", This()), g("g", This()),
              s("s", This()), t("t", This())
        {
        }

        Vec2(Vec2 &other)
            : Variable("vec2"),
              x("x", This()), y("y", This()),
              r("r", This()), g("g", This()),
              s("s", This()), t("t", This())
        {
            Parser::record("vec2" + this->get_expression() + " = " + other.get_expression());
        }

        Vec2(Float &f1, Float &f2)
            : Variable("vec2", "vec2(" + f1.get_expression() + ", " + f2.get_expression() + ")"),
              x("x", This()), y("y", This()),
              r("r", This()), g("g", This()),
              s("s", This()), t("t", This())
        {
        }

        Vec2 &operator=(const Vec2 &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }

        Vec2 &operator+(const Vec2 &other)
        {
            Vec2 *result = new Vec2(get_binary_expression("+", *this, other));
            return *result;
        }

        Vec2 &operator-(const Vec2 &other) 
        {
            Vec2 *result = new Vec2(get_binary_expression("-", *this, other));
            return *result;
        }

        Vec2 &operator*(const Vec2 &other) 
        {
            Vec2 *result = new Vec2(get_binary_expression("*", *this, other));
            return *result;
        }

        Vec2 &operator/(const Vec2 &other) 
        {
            Vec2 *result = new Vec2(get_binary_expression("/", *this, other));
            return *result;
        }

        Vec2 &operator*(const Float &other) 
        {
            Vec2 *result = new Vec2(get_binary_expression("*", *this, other));
            return *result;
        }

        Vec2 &operator/(const Float &other) 
        {
            Vec2 *result = new Vec2(get_binary_expression("/", *this, other));
            return *result;
        }

        static std::string get_type()
        {
            return "vec2";
        }
    };
}

#endif