#include "struct.h"

namespace GLSL
{
    Struct::Struct(const std::string &glsl_type)
        : Variable(glsl_type, Namer::name("va_", Parser::recorder.size(), glsl_type, ""))
    {
        Parser::record(glsl_type + " " + this->get_expression());
    }
}