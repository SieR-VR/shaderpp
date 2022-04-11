#include <iostream>

#include "program.h"

namespace GLSL
{   
    Shader::Shader(const std::string& version, const std::string& profile, const GLenum& type)
        : builder(version, profile)
    {
        this->id = glCreateShader(type);
    }
    
    void Shader::compile()
    {
        main();
        source = builder.build();

        const char* c_source = source.c_str();
        glShaderSource(this->id, 1, &c_source, nullptr);
        glCompileShader(this->id);

        GLint status;
        glGetShaderiv(this->id, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &length);
            std::string log(length, ' ');
            glGetShaderInfoLog(this->id, length, &length, &log[0]);
            std::cout << "[Shaderpp] Shader build failed: \n" << log << std::endl;
        }

        for (const auto& uniform : uniform_map)
            *uniform.second = glGetUniformLocation(this->id, uniform.first.c_str());
    }

    void Shader::register_uniform(const std::string& name, GLuint* p_location)
    {
        this->uniform_map[name] = p_location;
    }
}