#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <GL/glew.h>
#include <string>
#include <map>

#include "builder.h"

namespace GLSL
{
    class Shader
    {
    public:
        Builder builder;
        GLuint id;
        
        std::string source;
        std::map<std::string, GLuint *> uniform_map; 

        Shader(const std::string &version, const std::string &profile, const GLenum &type);
        void compile();
        void register_uniform(const std::string &name, GLuint *p_location);
        virtual void main() = 0;
    };
}

#endif