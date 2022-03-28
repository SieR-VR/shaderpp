#ifndef VEC2_H_
#define VEC2_H_

#include <initializer_list>

#include "../parser.h"
#include "../namer.h"
#include "float.h"

namespace GLSL {
    class Vec2 : public Variable {
        Vec2(std::string name, Context *context) {
            this->tree = new Tree(name, "vec2", ParentType::Argument);
            this->context = context;
        }

        Vec2(Vec2 &other) {
            this->tree = new Tree(Namer::next(), "vec2", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);
            this->context = other.context;

            context->record(this->tree, other.tree);
        }

        Vec2(Context *context, std::string parent_symbol, ParentType parent_type, std::initializer_list<Variable *> parents) {
            this->tree = new Tree(parent_symbol, "vec2", parent_type);
            this->context = context;
            for (Variable *parent : parents)
                this->tree->parents.push_back(parent->tree);
        }

        Vec2 &operator=(Vec2 &other) {
            this->tree = new Tree(this->tree->token, "vec2", ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);
            this->context = other.context;

            context->record(this->tree, other.tree);
            return *this;
        }

        Vec2 &operator+(Vec2 &other) {
            Vec2 *result = new Vec2(other.context, "+", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Vec2 &operator-(Vec2 &other) {
            Vec2 *result = new Vec2(other.context, "-", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Vec2 &operator*(Vec2 &other) {
            Vec2 *result = new Vec2(other.context, "*", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Vec2 &operator/(Vec2 &other) {
            Vec2 *result = new Vec2(other.context, "/", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Vec2 &operator*(Float &other) {
            Vec2 *result = new Vec2(other.context, "*", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Vec2 &operator/(Float &other) {
            Vec2 *result = new Vec2(other.context, "/", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        std::string get_declaration() {
            return "vec2 " + tree->token;
        }
    };
} // namespace GLSL

#endif