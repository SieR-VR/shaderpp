#ifndef STRUCT_H_
#define STRUCT_H_

#include "variable.h"

namespace GLSL
{
    class Struct : public Variable
    {
    public:
        Struct(const std::string &glsl_type) 
            : Variable(glsl_type, Namer::name("va_", Parser::recorder.size(), glsl_type, ""))
        {
            Parser::record(glsl_type + " " + this->get_expression()); 
        }
    };

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