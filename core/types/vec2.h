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
        Vec2(std::string symbol)
        {
            this->tree = new Tree(symbol, "vec2", ParentType::Argument);
        }

        Vec2(Vec2 &other)
        {
            this->tree = new Tree(Namer::next(), "vec2", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
        }

        Vec2(Float &f1, Float &f2)
        {
            this->tree = new Tree(Namer::next(), "vec2", ParentType::Declaration);
            this->tree->parents.push_back(f1.tree);
            this->tree->parents.push_back(f2.tree);

            record(this->tree);
        }
    };
}