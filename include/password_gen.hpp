#ifndef PASSWORD_GEN_HPP
#define PASSWORD_GEN_HPP

#include <string>

namespace generator {

// basic config
struct Config {
    int length = 16;
    bool useUpper = true;
    bool useLower = true;
    bool useDigits = true;
    bool useSymbols = true;
};

// generate a password based on config
std::string generate(const Config& cfg);

// optional: estimate entropy
double entropyBits(const std::string& password);

} // namespace generator

#endif
