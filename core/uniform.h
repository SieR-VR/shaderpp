#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <GL/glew.h>

#include "types/float.h"
#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

#include "program.h"

namespace GLSL
{
    template <class T>
    class Uniform : public T
    {};

    template <>
    class Uniform<Float> : public Float
    {
    public:
        GLuint location;
        
        Uniform(const std::string& name, Shader *shader) : Float(name) 
        {
            shader->builder.add_uniforms({ *this });
            shader->register_uniform(name, &location);
        }

        void set(const float &value)
        {
            glUniform1f(location, value);
        }
    };

    template <>
    class Uniform<Vec2> : public Vec2
    {
    public:
        GLuint location;
        
        Uniform(const std::string& name, Shader *shader) : Vec2(name) 
        {
            shader->builder.add_uniforms({ *this });
            shader->register_uniform(name, &location);
        }

        void set(const float &x, const float &y)
        {
            glUniform2f(location, x, y);
        }
    };

    template <>
    class Uniform<Vec3> : public Vec3
    {
    public:
        GLuint location;
        
        Uniform(const std::string& name, Shader *shader) : Vec3(name) 
        {
            shader->builder.add_uniforms({ *this });
            shader->register_uniform(name, &location);
        }

        void set(const float &x, const float &y, const float &z)
        {
            glUniform3f(location, x, y, z);
        }
    };

    template <>
    class Uniform<Vec4> : public Vec4
    {
    public:
        GLuint location;
        
        Uniform(const std::string& name, Shader *shader) : Vec4(name) 
        {
            shader->builder.add_uniforms({ *this });
            shader->register_uniform(name, &location);
        }

        void set(const float &x, const float &y, const float &z, const float &w)
        {
            glUniform4f(location, x, y, z, w);
        }
    };

    template <class T>
    class Input : public T
    {
    public:
        Input(const std::string& name, Shader *shader) : T(name) 
        {
            shader->builder.add_inputs({ *this });
        }
    };

    template <class T>
    class Output : public T
    {
    public:
        Output(const std::string& name, Shader *shader) : T(name) 
        {
            shader->builder.add_outputs({ *this });
        }

        Output<T> &operator=(const T &rhs)
        {
            T::operator=(rhs);
            return *this;
        }
    };
}

#endif