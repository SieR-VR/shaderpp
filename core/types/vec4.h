#ifndef VEC4_H_
#define VEC4_H_

#include "../variable.h"

#include "float.h"
#include "vec2.h"
#include "vec3.h"

namespace GLSL
{
    class Vec4 : public Variable
    {
    public:
        Float x, y, z, w, r, g, b, a, s, t, p, q;

        Vec4() = delete;

        Vec4(std::string symbol)
            : Variable("vec4", symbol),
              x("x", This()), y("y", This()), z("z", This()), w("w", This()),
              r("r", This()), g("g", This()), b("b", This()), a("a", This()),
              s("s", This()), t("t", This()), p("p", This()), q("q", This())
        {
        }

        Vec4(std::string symbol, std::weak_ptr<Variable> origin)
            : Variable("vec4", symbol, origin),
              x("x", This()), y("y", This()), z("z", This()), w("w", This()),
              r("r", This()), g("g", This()), b("b", This()), a("a", This()),
              s("s", This()), t("t", This()), p("p", This()), q("q", This())
        {
        }

        Vec4(const Vec4 &other)
            : Variable("vec4"),
              x("x", This()), y("y", This()), z("z", This()), w("w", This()),
              r("r", This()), g("g", This()), b("b", This()), a("a", This()),
              s("s", This()), t("t", This()), p("p", This()), q("q", This())
        {
            Parser::record("vec4 " + this->get_expression() + " = " + other.get_expression());
        }

        Vec4(const Float &f1, const Float &f2, const Float &f3, const Float &f4)
            : Variable("vec4", "vec4(" + f1.get_expression() + ", " + f2.get_expression() + ", " + f3.get_expression() + ", " + f4.get_expression() + ")"),
              x("x", This()), y("y", This()), z("z", This()), w("w", This()),
              r("r", This()), g("g", This()), b("b", This()), a("a", This()),
              s("s", This()), t("t", This()), p("p", This()), q("q", This())
        {
        }

        Vec4 &operator=(const Vec4 &other)
        {
            Parser::record(this->get_expression() + " = " + other.get_expression());
            return *this;
        }
    };
}

#endif