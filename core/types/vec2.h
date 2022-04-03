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

        Vec2(std::string symbol, ParentType parent_type = ParentType::Argument)
            : Variable(new Tree("vec2", symbol, ParentType::Argument)),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
        }

        Vec2(std::string symbol, Variable *origin)
            : Variable(new Tree("vec2", symbol, ParentType::Member, origin->tree)),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
        }

        Vec2(Vec2 &other)
            : Variable("vec2"),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
            record(this->tree);
        }

        Vec2(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
            : Variable(new Tree("vec2", parent_symbol, parent_type)),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);
        }

        Vec2(Float &f1, Float &f2)
            : Variable(new Tree("vec2", "", ParentType::Constructor)),
              x("x", this), y("y", this),
              r("r", this), g("g", this),
              s("s", this), t("t", this)
        {
            this->tree->parents.push_back(f1.tree);
            this->tree->parents.push_back(f2.tree);

            record(this->tree);
        }

        Vec2 &operator=(const Vec2 &other)
        {
            this->tree = new Tree("vec2", get_symbol(), ParentType::AssignOperator);
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