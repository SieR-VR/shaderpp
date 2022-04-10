#ifndef VEC3_H_
#define VEC3_H_

#include "../variable.h"

#include "float.h"
#include "vec2.h"

namespace GLSL
{
    class Vec3 : public Variable
    {
    public:
        Float x, y, z, r, g, b, s, t, p;

        Vec3() = delete;

        Vec3(std::string symbol)
            : Variable("vec3", symbol),
              x("x", this), y("y", this), z("z", this),
              r("r", this), g("g", this), b("b", this),
              s("s", this), t("t", this), p("p", this)
        {
        }

        Vec3(std::string symbol, Variable *origin)
            : Variable("vec3", symbol, origin),
              x("x", this), y("y", this), z("z", this),
              r("r", this), g("g", this), b("b", this),
              s("s", this), t("t", this), p("p", this)
        {
        }

        Vec3(Vec3 &other)
            : Variable("vec3"),
              x("x", this), y("y", this), z("z", this),
              r("r", this), g("g", this), b("b", this),
              s("s", this), t("t", this), p("p", this)
        {
            Parser::record("vec3 " + this->get_expression() + " = " + other.get_expression());
        }

        Vec3(Float &f1, Float &f2, Float &f3)
            : Variable("vec3", "vec3(" + f1.get_expression() + ", " + f2.get_expression() + ", " + f3.get_expression() + ")"),
              x("x", this), y("y", this), z("z", this),
              r("r", this), g("g", this), b("b", this),
              s("s", this), t("t", this), p("p", this)
        {
        }

        Vec3 &operator=(const Vec3 &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }

        Vec3 &operator+(Vec3 &other)
        {
            Vec3 *result = new Vec3(bin_exp("+", this, &other));
            return *result;
        }

        Vec3 &operator-(Vec3 &other)
        {
            Vec3 *result = new Vec3(bin_exp("-", this, &other));
            return *result;
        }

        Vec3 &operator*(Vec3 &other)
        {
            Vec3 *result = new Vec3(bin_exp("*", this, &other));
            return *result;
        }

        Vec3 &operator/(Vec3 &other)
        {
            Vec3 *result = new Vec3(bin_exp("/", this, &other));
            return *result;
        }

        Vec3 &operator*(Float &other)
        {
            Vec3 *result = new Vec3(bin_exp("*", this, &other));
            return *result;
        }

        Vec3 &operator/(Float &other)
        {
            Vec3 *result = new Vec3(bin_exp("/", this, &other));
            return *result;
        }

        Vec3 &operator-()
        {
            Vec3 *result = new Vec3(un_exp("-", this));
            return *result;
        }
    };
}

#endif