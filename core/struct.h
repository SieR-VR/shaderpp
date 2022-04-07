#ifndef STRUCT_H_
#define STRUCT_H_

#include "variable.h"

namespace GLSL
{
    template <typename T>
    class Struct
    {
    public:
        std::string declaration;
        std::string definition;
        std::string symbol;

        Struct()
        {
            T *t = new T();

            this->symbol = t->glsl_type;
            this->declaration = "struct " + this->symbol + ";\n";
            this->definition = "struct " + this->symbol + " {\n";

            for (Variable *v : t->branches)
                this->definition += "\t" + v->get_declaration() + ";\n";

            this->definition += "};\n";
        }
    };
}

#endif