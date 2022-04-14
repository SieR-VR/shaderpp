#include <iostream>

#include "program.h"

namespace GLSL
{   
    Shader::Shader(const std::string& version, const std::string& profile)
        : builder(version, profile)
    {
    }
    
    void Shader::compile()
    {
        main();
        source = builder.build();
    }
}