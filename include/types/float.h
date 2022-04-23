#ifndef FLOAT_H_
#define FLOAT_H_

#include "../variable.h"

namespace GLSL
{
    class Float : public Variable
    {
    public:
        Float() = delete;

        Float(std::string expression);
        Float(std::string token, Variable* origin);
        Float(const Float &other);
        Float(float value);

        void *operator new(size_t size);
        Float &operator=(const Float &other);
        Float &operator+(const Float &other);
        Float &operator-(const Float &other);
        Float &operator*(const Float &other);
        Float &operator/(const Float &other);

        static std::string get_type();
    };
}

#endif