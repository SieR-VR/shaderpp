#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>
#include <map>

#include "builder.h"

namespace GLSL
{
    class Shader
    {
    public:
        Builder builder;
        
        std::string source;

        Shader(const std::string &version, const std::string &profile);
        void compile();
        virtual void main() = 0;
    };
}

#endif