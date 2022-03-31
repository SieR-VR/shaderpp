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
        {
            this->tree = new Tree(name, "float", parent_type);
        }

        Float(Float &other)
        {
            this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
        }

        Float(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
        {
            this->tree = new Tree(parent_symbol, "float", parent_type);
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);
        }

        Float &operator=(Float &other)
        {
            this->tree = new Tree(get_symbol(), "float", ParentType::AssignOperator);
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