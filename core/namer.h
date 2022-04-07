#ifndef NAMER_H_
#define NAMER_H_

#include <string>
#include <sstream>
#include <iomanip>
#include <functional>

class Namer
{
public:
    static std::string name(std::string prefix, int line, std::string type, std::string nonce) {
        static std::hash<std::string> hash_fn;

        std::stringstream stream;
        stream << prefix
               << std::setfill('0') << std::setw(8)
               << std::hex << (hash_fn(std::to_string(line) + type + nonce) & 0xFFFFFFFF);

        return stream.str();
    }
};

#endif