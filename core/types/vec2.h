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

        Vec2(const std::string& symbol)
            : Variable("vec2", symbol),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
        }

        Vec2(const std::string& symbol, Variable* origin)
            : Variable("vec2", symbol, origin),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
        }

        Vec2(const Vec2 &other)
            : Variable("vec2"),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
            Parser::record("vec2 " + this->get_expression() + " = " + other.get_expression());
        }

        Vec2(const Float &f1, const Float &f2)
            : Variable("vec2", "vec2(" + f1.get_expression() + ", " + f2.get_expression() + ")"),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
        }

        void *operator new(size_t size)
        {
            return Variable::operator new(size);
        }

        Vec2 &operator=(const Vec2 &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }

        Vec2 &operator+(Vec2 &other) const
        {
            Vec2 *result = new Vec2(bin_exp("+", this, &other));
            return *result;
        }

        Vec2 &operator-(Vec2 &other) const
        {
            Vec2 *result = new Vec2(bin_exp("-", this, &other));
            return *result;
        }

        Vec2 &operator*(Vec2 &other) const
        {
            Vec2 *result = new Vec2(bin_exp("*", this, &other));
            return *result;
        }

        Vec2 &operator/(Vec2 &other) const
        {
            Vec2 *result = new Vec2(bin_exp("/", this, &other));
            return *result;
        }

        Vec2 &operator*(Float &other) const
        {
            Vec2 *result = new Vec2(bin_exp("*", this, &other));
            return *result;
        }

        Vec2 &operator/(Float &other) const
        {
            Vec2 *result = new Vec2(bin_exp("/", this, &other));
            return *result;
        }

        static std::string get_type()
        {
            return "vec2";
        }
    };
}

#endif