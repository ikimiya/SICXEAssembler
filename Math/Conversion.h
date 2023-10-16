// __Conversion.h__


#ifndef __CONVERSION_H_
#define __CONVERSION_H_

#include <string>
#include <iostream>
#include <sstream>

class Conversion
{
    public:

    Conversion();

    ~Conversion();

    void convertBinToHex(int binary);

    std::string binaryToHex(int binary);

    int hexToBinary(std::string hex);

    int stringToInt(std::string string);

    std::string intToString(int number);




};

#endif
