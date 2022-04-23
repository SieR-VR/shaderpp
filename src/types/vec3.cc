#include "types/vec3.h"

namespace GLSL
{
    Vec3::Vec3(const std::string& symbol)
        : Variable("vec3", symbol),
          x("x", this), y("y", this), z("z", this),
          r("r", this), g("g", this), b("b", this),
          s("s", this), t("t", this), p("p", this)
    {
    }

    Vec3::Vec3(const std::string& symbol, Variable* origin)
        : Variable("vec3", symbol, origin),
          x("x", this), y("y", this), z("z", this),
          r("r", this), g("g", this), b("b", this),
          s("s", this), t("t", this), p("p", this)
    {
    }

    Vec3::Vec3(const Vec3 &other)
        : Variable("vec3"),
          x("x", this), y("y", this), z("z", this),
          r("r", this), g("g", this), b("b", this),
          s("s", this), t("t", this), p("p", this)
    {
        Parser::record("vec3 " + this->get_expression() + " = " + other.get_expression());
    }

    Vec3::Vec3(const Float &f1, const Float &f2, const Float &f3)
        : Variable("vec3", "vec3(" + f1.get_expression() + ", " + f2.get_expression() + ", " + f3.get_expression() + ")"),
          x("x", this), y("y", this), z("z", this),
          r("r", this), g("g", this), b("b", this),
          s("s", this), t("t", this), p("p", this)
    {
    }

    void *Vec3::operator new(size_t size)
    {
        return Variable::operator new(size);
    }

    Vec3 &Vec3::operator=(const Vec3 &other)
    {
        Parser::record(this->get_expression() + " = " + other.get_expression());
        return *this;
    }

    Vec3 &Vec3::operator+(const Vec3 &other)
    {
        Vec3 *result = new Vec3(bin_exp("+", other));
        return *result;
    }

    Vec3 &Vec3::operator-(const Vec3 &other)
    {
        Vec3 *result = new Vec3(bin_exp("-", other));
        return *result;
    }

    Vec3 &Vec3::operator*(const Vec3 &other)
    {
        Vec3 *result = new Vec3(bin_exp("*", other));
        return *result;
    }

    Vec3 &Vec3::operator/(const Vec3 &other)
    {
        Vec3 *result = new Vec3(bin_exp("/", other));
        return *result;
    }

    Vec3 &Vec3::operator*(const Float &other)
    {
        Vec3 *result = new Vec3(bin_exp("*", other));
        return *result;
    }

    Vec3 &Vec3::operator/(const Float &other)
    {
        Vec3 *result = new Vec3(bin_exp("/", other));
        return *result;
    }

    Vec3 &Vec3::operator-()
    {
        Vec3 *result = new Vec3(un_exp("-"));
        return *result;
    }

    std::string Vec3::get_type()
    {
        return "vec3";
    }
}