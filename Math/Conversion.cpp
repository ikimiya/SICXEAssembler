// __Conversion.cpp__


#include "Conversion.h"




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


