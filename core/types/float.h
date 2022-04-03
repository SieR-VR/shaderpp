#ifndef FLOAT_H_
#define FLOAT_H_

#include "../parser.h"
#include "../namer.h"

namespace GLSL
{
    class Float : public Variable
    {
    public:
        Float() = delete;

        Float(std::string name, ParentType parent_type = ParentType::Argument)
            : Variable(new Tree("float", name, parent_type))
        {
        }

        Float(std::string name, Variable *origin)
            : Variable(new Tree("float", name, ParentType::Member, origin->tree))
        {
        }

        Float(Float &other)
            : Variable("float")
        {
            this->tree->parents.push_back(other.tree);
            record(this->tree);
        }

        Float(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
            : Variable(new Tree("float", parent_symbol, parent_type))
        {
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);
        }

        Float &operator=(Float &other)
        {
            this->tree = new Tree("float", get_symbol(), ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
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
    };
}

#endif