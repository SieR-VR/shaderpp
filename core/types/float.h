#ifndef FLOAT_H_
#define FLOAT_H_

#include <initializer_list>

#include "../parser.h"
#include "../namer.h"

namespace GLSL
{
    class Float : public Variable
    {
    public:
        Float(std::string name, Context *context)
        {
            this->tree = new Tree(name, "float", ParentType::Argument);
            this->context = context;
        }

        Float(Float &other)
        {
            this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);
            this->context = other.context;

            context->record(this->tree, other.tree);
        }

        Float(Context *context, std::string parent_symbol, ParentType parent_type, std::initializer_list<Variable *> parents)
        {
            this->tree = new Tree(parent_symbol, "float", parent_type);
            this->context = context;
            for (Variable *parent : parents)
                this->tree->parents.push_back(parent->tree);
        }

        Float &operator=(Float &other)
        {
            this->tree = new Tree(this->tree->token, "float", ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);
            this->context = other.context;

            context->record(this->tree, other.tree);
            return *this;
        }

        Float &operator+(Float &other)
        {
            Float *result = new Float(other.context, "+", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Float &operator-(Float &other)
        {
            Float *result = new Float(other.context, "-", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Float &operator*(Float &other)
        {
            Float *result = new Float(other.context, "*", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Float &operator/(Float &other)
        {
            Float *result = new Float(other.context, "/", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        Float &operator%(Float &other)
        {
            Float *result = new Float(other.context, "%", ParentType::BinaryOperator, {this, &other});
            return *result;
        }

        std::string get_declaration()
        {
            return "float " + tree->token;
        }
    };
}

#endif