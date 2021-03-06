#ifndef STRUCT_H_
#define STRUCT_H_

#include "variable.h"

namespace GLSL
{
    /**
     * @brief The Struct class represents a structure in the GLSL language.
     */
    class Struct : public Variable
    {
    public:
        Struct(const std::string &glsl_type);
    };

    /**
     * @brief The StructDecl helper class for store the declaration of a structure.
     * @tparam T The type of the structure that inherits from Struct.
     */
    template <class T>
    class StructDecl 
    {
    public:
        std::string glsl_type;
        std::string declaration;
        std::string definition;

        StructDecl()
        {
            T *t = new T();
            glsl_type = t->glsl_type;

            declaration = "struct " + glsl_type + ";\n";

            definition = "struct " + glsl_type + " {\n";
            for (auto branch : t->branches)
                definition += "\t" + branch->glsl_type + " " + branch->expression + ";\n";
            definition += "};\n";
        }
    };
}

#endif