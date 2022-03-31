#ifndef VEC2_H_
#define VEC2_H_

#include "../parser.h"
#include "../namer.h"

#include "float.h"

namespace GLSL
{
    class Vec2 : public Variable
    {
    public:
        Float x, y, r, g, s, t;

        Vec2() = delete;

        Vec2(std::string symbol)
            : x("x"), y("y"), r("r"), g("g"), s("s"), t("t")
        {
            this->tree = new Tree(symbol, "vec2", ParentType::Argument);

            x.set_origin(this->tree);
            y.set_origin(this->tree);

            r.set_origin(this->tree);
            g.set_origin(this->tree);

            s.set_origin(this->tree);
            t.set_origin(this->tree);
        }

        Vec2(Vec2 &other)
            : x("x"), y("y"), r("r"), g("g"), s("s"), t("t")
        {
            this->tree = new Tree(Namer::next(), "vec2", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);

            record(this->tree);

            x.set_origin(this->tree);
            y.set_origin(this->tree);

            r.set_origin(this->tree);
            g.set_origin(this->tree);

            s.set_origin(this->tree);
            t.set_origin(this->tree);
        }

        Vec2(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
            : x("x"), y("y"), r("r"), g("g"), s("s"), t("t")
        {
            this->tree = new Tree(parent_symbol, "vec2", parent_type);
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);

            x.set_origin(this->tree);
            y.set_origin(this->tree);

            r.set_origin(this->tree);
            g.set_origin(this->tree);

            s.set_origin(this->tree);
            t.set_origin(this->tree);
        }

        Vec2(Float &f1, Float &f2)
            : x("x"), y("y"), r("r"), g("g"), s("s"), t("t")
        {
            this->tree = new Tree("", "vec2", ParentType::Constructor);
            this->tree->parents.push_back(f1.tree);
            this->tree->parents.push_back(f2.tree);

            record(this->tree);

            x.set_origin(this->tree);
            y.set_origin(this->tree);

            r.set_origin(this->tree);
            g.set_origin(this->tree);

            s.set_origin(this->tree);
            t.set_origin(this->tree);
        }

        Vec2 &operator=(const Vec2 &other)
        {
            this->tree = new Tree(get_symbol(), "vec2", ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
            return *this;
        }

        Vec2 &operator+(const Vec2 &other)
        {
            Vec2 *result = new Vec2("+", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Vec2 &operator-(const Vec2 &other)
        {
            Vec2 *result = new Vec2("-", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Vec2 &operator*(const Vec2 &other)
        {
            Vec2 *result = new Vec2("*", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Vec2 &operator/(const Vec2 &other)
        {
            Vec2 *result = new Vec2("/", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Vec2 &operator*(const Float &other)
        {
            Vec2 *result = new Vec2("*", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Vec2 &operator/(const Float &other)
        {
            Vec2 *result = new Vec2("/", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }
    };
}

#endif