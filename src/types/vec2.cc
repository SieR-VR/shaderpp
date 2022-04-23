#include "types/vec2.h"

namespace GLSL
{
    Vec2::Vec2(const std::string& symbol)
        : Variable("vec2", symbol),
          x("x", this), y("y", this),
          r("r", this), g("g", this),
          s("s", this), t("t", this)
    {
    }

    Vec2::Vec2(const std::string& symbol, Variable* origin)
        : Variable("vec2", symbol, origin),
          x("x", this), y("y", this),
          r("r", this), g("g", this),
          s("s", this), t("t", this)
    {
    }

    Vec2::Vec2(const Vec2 &other)
        : Variable("vec2"),
          x("x", this), y("y", this),
          r("r", this), g("g", this),
          s("s", this), t("t", this)
    {
        Parser::record("vec2 " + this->get_expression() + " = " + other.get_expression());
    }

    Vec2::Vec2(const Float &f1, const Float &f2)
        : Variable("vec2", "vec2(" + f1.get_expression() + ", " + f2.get_expression() + ")"),
          x("x", this), y("y", this),
          r("r", this), g("g", this),
          s("s", this), t("t", this)
    {
    }

    void *Vec2::operator new(size_t size)
    {
        return Variable::operator new(size);
    }

    Vec2 &Vec2::operator=(const Vec2 &other)
    {
        Parser::record(this->get_expression() + " = " + other.get_expression());
        return *this;
    }

    Vec2 &Vec2::operator+(const Vec2 &other) const
    {
        Vec2 *result = new Vec2(bin_exp("+", other));
        return *result;
    }
    
    Vec2 &Vec2::operator-(const Vec2 &other) const
    {
        Vec2 *result = new Vec2(bin_exp("-", other));
        return *result;
    }

    Vec2 &Vec2::operator*(const Vec2 &other) const
    {
        Vec2 *result = new Vec2(bin_exp("*", other));
        return *result;
    }

    Vec2 &Vec2::operator/(const Vec2 &other) const
    {
        Vec2 *result = new Vec2(bin_exp("/", other));
        return *result;
    }

    Vec2 &Vec2::operator*(const Float &other) const
    {
        Vec2 *result = new Vec2(bin_exp("*", other));
        return *result;
    }
    
    Vec2 &Vec2::operator/(const Float &other) const
    {
        Vec2 *result = new Vec2(bin_exp("/", other));
        return *result;
    }

    std::string Vec2::get_type()
    {
        return "vec2";
    }
}