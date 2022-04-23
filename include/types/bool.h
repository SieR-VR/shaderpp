#ifndef BOOL_H_
#define BOOL_H_

#include "../variable.h"

namespace GLSL
{
    class Bool : public Variable
    {
    public:
        Bool() = delete;

        Bool(std::string expression);
        Bool(std::string token, Variable *origin);
        Bool(const Bool &other);
        Bool(bool value);

        void *operator new(size_t size);

        Bool &operator=(const Bool &other);
        Bool &operator!();
        Bool &operator&&(const Bool &other);
        Bool &operator||(const Bool &other);
        operator bool();

        static std::string get_type();
    };
}

#endif