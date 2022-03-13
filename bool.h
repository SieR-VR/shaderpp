#ifndef BOOL_H_
#define BOOL_H_

#include <initializer_list>

#include "parser.h"
#include "namer.h"

class Bool : public Variable
{
public:
    Bool(std::string name) {
        this->tree = new Tree(name, "float", ParentType::Argument);
    }

    Bool(Bool &other) {
        this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
        this->tree->parents.push_back(other.tree);
        other.tree->children.push_back(this->tree);
    }

    Bool(std::string parent_symbol, ParentType parent_type, std::initializer_list<Variable*> parents) {
        this->tree = new Tree(parent_symbol, "float", parent_type);
        for (Variable *parent : parents) {
            this->tree->parents.push_back(parent->tree);
            parent->tree->children.push_back(this->tree);
        }
    }

    Bool& operator=(Bool &other)
    {
        this->tree = new Tree(Namer::next(), "float", ParentType::Declaration);
        this->tree->parents.push_back(other.tree);
        other.tree->children.push_back(this->tree);
        return *this;
    }
    
    Bool& operator+(Bool &other)
    {
        Bool *result = new Bool("+", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Bool& operator-(Bool &other)
    {
        Bool *result = new Bool("-", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Bool& operator*(Bool &other)
    {
        Bool *result = new Bool("*", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    operator bool()
    {

    }
};

#endif