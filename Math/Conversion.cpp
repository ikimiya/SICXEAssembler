// __Conversion.cpp__


#include "Conversion.h"

#include <iomanip>
#include <bitset>


Conversion::Conversion()
{

}

Conversion::~Conversion()
{

}

void Conversion::convertBinToHex(int binary)
{

    //int decimal_value = std::stoi(hex_value, nullptr, 16)


    auto res = (std::stringstream{} << std::hex << binary).str();

    //std::stringstream ss;
    //ss << std::hex << binary;
    //std::string res (ss.str());

    std::cout << res << std::endl;


}


std::string Conversion::binaryToHex(int binary)
{
    auto res = (std::stringstream{} << std::hex << binary).str();

    return res;
}

int Conversion::hexToBinary(std::string hex)
{
    int value = std::stoi(hex,nullptr,16);

    return value;

}

int Conversion::stringToInt(std::string word)
{
    int value = std::stoi(word);
    return value;
}

std::string Conversion::intToString(int number)
{
    std::string strNum = std::to_string(number);

    return strNum;
}

std::string Conversion::binaryToHexByte(int number)
{
    //std::string hex = binaryToHex(number);
    std::stringstream ss;

    ss << std::setfill('0') << std::setw(4) << std::hex << number;
   
    return ss.str();
}

std::string Conversion::decimalToHexFour(int number)
{

    long long unsigned int n = number;

    std::stringstream ss;

    // 0101 0100

    ss << std::bitset<4>{n};
    
    return ss.str();
}


std::string Conversion::decimalToHexTwo(int number)
{

    long long unsigned int n = number;

    std::stringstream ss;
    ss << std::bitset<4>{n};

    return ss.str().erase(2);
}


