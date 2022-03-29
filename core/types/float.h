#ifndef FLOAT_H_
#define FLOAT_H_

#include "../parser.h"
#include "../namer.h"

namespace GLSL
{
    class Float : public Variable
    {
    public:
        Float(std::string name)
        {
            this->tree = new Tree(name, "float", ParentType::Argument);
        }

        Float(Float &other)
        {
            this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);

            record(this->tree, other.tree);
        }

        Float(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
        {
            this->tree = new Tree(parent_symbol, "float", parent_type);
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);
        }

        Float &operator=(Float &other)
        {
            this->tree = new Tree(this->tree->token, "float", ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);

            record(this->tree, other.tree);
            return *this;
        }

        Float &operator+(Float &other)
        {
            Float *result = new Float("+", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Float &operator-(Float &other)
        {
            Float *result = new Float("-", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Float &operator*(Float &other)
        {
            Float *result = new Float("*", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Float &operator/(Float &other)
        {
            Float *result = new Float("/", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        Float &operator%(Float &other)
        {
            Float *result = new Float("%", ParentType::BinaryOperator, {this->tree, other.tree});
            return *result;
        }

        std::string get_declaration()
        {
            return "float " + tree->token;
        }
    };
}

#endif