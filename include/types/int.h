#ifndef INT_H_
#define INT_H_

#include "../variable.h"

namespace GLSL
{
    class Int : public Variable
    {
    public:
        Int() = delete;

        Int(std::string expression);
        Int(std::string name, Variable* origin);
        Int(const Int &other);

        void *operator new(size_t size);
        Int &operator=(const Int &other);
        
        static std::string get_type();
    };
}

#endif