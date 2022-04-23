#include <sstream>
#include <iomanip>
#include <functional>

#include "namer.h"

std::string Namer::name(const std::string &prefix, const int &line, const std::string &type, const std::string &nonce)
{
    static std::hash<std::string> hash_fn;

    std::stringstream stream;
    stream << prefix
           << std::setfill('0') << std::setw(8)
           << std::hex << (hash_fn(std::to_string(line) + type + nonce) & 0xFFFFFFFF);

    return stream.str();
}