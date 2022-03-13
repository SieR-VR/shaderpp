#ifndef NAMER_H_
#define NAMER_H_

#include <string>

class Namer
{
public:
    static std::string next() {
        static int i = 0;
        return "v" + std::to_string(i++);
    }
};

#endif