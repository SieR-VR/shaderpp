#include "types/vec4.h"

namespace GLSL
{
    Vec4::Vec4(const std::string &symbol)
        : Variable("vec4", symbol),
          x("x", this), y("y", this), z("z", this), w("w", this),
          r("r", this), g("g", this), b("b", this), a("a", this),
          s("s", this), t("t", this), p("p", this), q("q", this)
    {
    }

    Vec4::Vec4(const std::string &symbol, Variable* origin)
        : Variable("vec4", symbol, origin),
          x("x", this), y("y", this), z("z", this), w("w", this),
          r("r", this), g("g", this), b("b", this), a("a", this),
          s("s", this), t("t", this), p("p", this), q("q", this)
    {
    }

    Vec4::Vec4(const Vec4 &other)
        : Variable("vec4"),
          x("x", this), y("y", this), z("z", this), w("w", this),
          r("r", this), g("g", this), b("b", this), a("a", this),
          s("s", this), t("t", this), p("p", this), q("q", this)
    {
        Parser::record("vec4 " + this->get_expression() + " = " + other.get_expression());
    }

    Vec4::Vec4(const Float &f1, const Float &f2, const Float &f3, const Float &f4)
        : Variable("vec4", "vec4(" + f1.get_expression() + ", " + f2.get_expression() + ", " + f3.get_expression() + ", " + f4.get_expression() + ")"),
          x("x", this), y("y", this), z("z", this), w("w", this),
          r("r", this), g("g", this), b("b", this), a("a", this),
          s("s", this), t("t", this), p("p", this), q("q", this)
    {
    }

    void* Vec4::operator new(size_t size)
    {
        return Variable::operator new(size);
    }

    Vec4& Vec4::operator=(const Vec4 &other)
    {
        Parser::record(this->get_expression() + " = " + other.get_expression());
        return *this;
    }

    std::string Vec4::get_type()
    {
        return "vec4";
    }
}