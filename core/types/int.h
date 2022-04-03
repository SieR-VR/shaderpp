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
            : Variable(new Tree("int", name, parent_type))
        {
        }

        Int(std::string name, Variable *origin)
            : Variable(new Tree("int", name, ParentType::Member, origin->tree))
        {
        }

        Int(Int &other)
            : Variable("int")
        {
            this->tree->parents.push_back(other.tree);
            record(this->tree);
        }

        Int(std::string parent_symbol, ParentType parent_type, std::vector<Tree *> parents)
            : Variable(new Tree("int", parent_symbol, parent_type))
        {
            for (Tree *parent : parents)
                this->tree->parents.push_back(parent);
        }

        Int &operator=(Int &other)
        {
            this->tree = new Tree("int", get_symbol(), ParentType::AssignOperator);
            this->tree->parents.push_back(other.tree);

            record(this->tree);
            return *this;
        }
    };
}

#endif