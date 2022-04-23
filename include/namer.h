#ifndef NAMER_H_
#define NAMER_H_

#include <string>

class Namer
{
public:
    static std::string name(const std::string& prefix, const int& line, const std::string& type, const std::string& nonce);
};

#endif