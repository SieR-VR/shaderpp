#ifndef UNIFORM_H_
#define UNIFORM_H_

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
    
        Uniform(const std::string& name, Shader *shader) : Float(name) 
        {
            shader->builder.add_uniforms({ *this });
        }

        void set(const float &value)
        {
        }
    };

    template <>
    class Uniform<Vec2> : public Vec2
    {
    public:
        
        Uniform(const std::string& name, Shader *shader) : Vec2(name) 
        {
            shader->builder.add_uniforms({ *this });
        }

        void set(const float &x, const float &y)
        {
        }
    };

    template <>
    class Uniform<Vec3> : public Vec3
    {
    public:
        
        Uniform(const std::string& name, Shader *shader) : Vec3(name) 
        {
            shader->builder.add_uniforms({ *this });
        }

        void set(const float &x, const float &y, const float &z)
        {
        }
    };

    template <>
    class Uniform<Vec4> : public Vec4
    {
    public:
        
        Uniform(const std::string& name, Shader *shader) : Vec4(name) 
        {
            shader->builder.add_uniforms({ *this });
        }

        void set(const float &x, const float &y, const float &z, const float &w)
        {
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