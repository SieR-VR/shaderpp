#ifndef FLOAT_H_
#define FLOAT_H_

#include <initializer_list>

#include "parser.h"
#include "namer.h"

class Float : public Variable
{
public:
    Float(std::string name) {
        this->tree = new Tree(name, "float", ParentType::Argument);
    }

    Float(Float &other) {
        this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
        this->tree->parents.push_back(other.tree);
        other.tree->children.push_back(this->tree);
    }

    Float(std::string parent_symbol, ParentType parent_type, std::initializer_list<Variable*> parents) {
        this->tree = new Tree(parent_symbol, "float", parent_type);
        for (Variable *parent : parents) {
            this->tree->parents.push_back(parent->tree);
            parent->tree->children.push_back(this->tree);
        }
    }

    Float& operator=(Float &other)
    {
        this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
        this->tree->parents.push_back(other.tree);
        other.tree->children.push_back(this->tree);
        return *this;
    }
    
    Float& operator+(Float &other)
    {
        Float *result = new Float("+", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Float& operator-(Float &other)
    {
        Float *result = new Float("-", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Float& operator*(Float &other)
    {
        Float *result = new Float("*", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Float& operator/(Float &other)
    {
        Float *result = new Float("/", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Float& operator%(Float &other)
    {
        Float *result = new Float("%", ParentType::BinaryOperator, {this, &other});
        return *result;
    }
};

#endif