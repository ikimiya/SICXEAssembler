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


    // convert int number to hex
    std::string binaryToHex(int binary);

    // convert hex number to int
    int hexToBinary(std::string hex);


    int stringToInt(std::string string);
    std::string intToString(int number);

    // writing text
    std::string binaryToHexByte(int number);

    std::string opcodeHex(std::string number);

    // format 4 opcode 8 
    std::string decimalToHexFour(int number);
    std::string decimalToHexFour(std::string number);

    // format 3 opcode 6
    std::string decimalToHexTwo(int number);
    std::string decimalToHexTwo(std::string number);

    // convert displacement bits to opcode
    std::string displacement(int number);

    std::string displacementExtend(int number);

    std::string byteCalc(std::string input);
    std::string fillHex(std::string input);
    std::string fillHexNum(std::string input, int num);
    std::string fillHexNum(int input, int num);

    // check Header length
    std::string checkLength(std::string length);

    








};

#endif
