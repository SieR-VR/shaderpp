#ifndef BOOL_H_
#define BOOL_H_

#include <initializer_list>

#include "parser.h"
#include "namer.h"

class Bool : public Variable
{
public:
    Bool(std::string name, Context *context)
    {
        this->tree = new Tree(name, "bool", ParentType::Argument);
        this->context = context;
    }

    Bool(Bool &other)
    {
        this->tree = new Tree(Namer::next(), "bool", ParentType::Declaration);
        this->tree->parents.push_back(other.tree);
        this->context = other.context;

        context->record(this->tree, other.tree);
    }

    Bool(Context *context, std::string parent_symbol, ParentType parent_type, std::initializer_list<Variable *> parents)
    {
        this->tree = new Tree(parent_symbol, "bool", parent_type);
        this->context = context;
        for (Variable *parent : parents)
            this->tree->parents.push_back(parent->tree);
    }

    Bool &operator=(Bool &other)
    {
        this->tree = new Tree(Namer::next(), "bool", ParentType::Declaration);
        this->tree->parents.push_back(other.tree);
        this->context = other.context;

        context->record(this->tree, other.tree);
        return *this;
    }

    Bool &operator+(Bool &other)
    {
        Bool *result = new Bool(other.context, "+", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Bool &operator-(Bool &other)
    {
        Bool *result = new Bool(other.context, "-", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    Bool &operator*(Bool &other)
    {
        Bool *result = new Bool(other.context, "*", ParentType::BinaryOperator, {this, &other});
        return *result;
    }

    operator bool()
    {
        return this->context->enter_if(this->tree);
    }

    std::string get_declaration() {
        return "bool " + tree->token;
    }
};

#endif