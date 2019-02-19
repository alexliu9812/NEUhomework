#ifndef CONVERSION_H
#define CONVERSION_H
#include <string>

class Conversion
{
public:
    Conversion();
    std::string hex(std::string s);
    std::string ascii(std::string s);
    int hexToInt(std::string s);
    std::string getStrings(std::string s);
};

#endif // CONVERSION_H
