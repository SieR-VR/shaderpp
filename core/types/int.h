#ifndef INT_H_
#define INT_H_

#include "../parser.h"
#include "../namer.h"

namespace GLSL
{
    class Int : public Variable
    {
    public:
        Int() = delete;

        Int(std::string name, ParentType parent_type = ParentType::Argument)
        {
            this->tree = new Tree(name, "int", parent_type);
        }

        Int(Int &other)
        {
            this->tree = new Tree(Namer::next(), "int", ParentType::Declaration);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
        }

        Int(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
        {
            this->tree = new Tree(parent_symbol, "int", parent_type);
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);
        }

        Int &operator=(Int &other)
        {
            this->tree = new Tree(get_symbol(), "int", ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
            return *this;
        }
    };
}

#endif