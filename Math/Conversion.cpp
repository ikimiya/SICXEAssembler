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
    auto res = (std::stringstream{} << std::hex << std::uppercase << binary).str();

    return res;
}

int Conversion::hexToBinary(std::string hex)
{
    int value = std::stoi(hex,nullptr,16);

    return value;

}

int Conversion::stringToInt(std::string word)
{
    //std::cout << "ERROR checking: " << word << std::endl;
    int value;
    try
    {
        value = std::stoi(word);

    }
    catch(const std::exception& e)
    {
        std::cout << "Stoi String To Int Error: " << e.what() << ": " << word << std::endl;
    }
    
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

std::string Conversion::opcodeHex(std::string number)
{
    //std::string hex = binaryToHex(number);
    std::stringstream ss;

    // result to upper case
    ss << std::uppercase;
    
    // loop 0-4 each time to read each 4 bits
    for (int i = 0; i < number.length(); i += 4) {
        
        // split 4 strings 
        std::string hex = number.substr(i, 4);
        int decimalValue = std::bitset<4>(hex).to_ulong();
        ss << std::hex << decimalValue; 
    }
    return ss.str();
}


std::string Conversion::decimalToHexTwo(int number)
{
    // 0101 01 
    long long unsigned int n = number;

    std::stringstream ss;
    ss << std::bitset<4>{n};

    return ss.str().erase(2);
}

std::string Conversion::decimalToHexFour(std::string number)
{
    // 0101 0100
    long long unsigned int n = hexToBinary(number);

    std::stringstream ss;
    ss << std::setw(8) << std::setfill('0') << std::bitset<8>{n};
    return ss.str();
}


std::string Conversion::decimalToHexFour(int number)
{
    // 0101 0100

    long long unsigned int n = number;
    std::stringstream ss;

    ss << std::bitset<4>{n};

    return ss.str();
}



std::string Conversion::decimalToHexTwo(std::string number)
{

    long long unsigned int n = hexToBinary(number);
    std::stringstream ss;

    ss << std::setw(8) << std::setfill('0') << std::bitset<8>{n};

    std::string save = ss.str();
    save.erase(save.size() -2);

    //std::cout << "number: " << ss.str() << std::endl;
    //std::cout << "save: " << save << std::endl;

    return ss.str().erase(ss.str().size() - 2);
}


// get binary number and convert to hex
std::string Conversion::displacement(int number)
{

    long long unsigned int n = (number);

    std::stringstream ss;
    ss << std::setw(12) << std::setfill('0') << std::bitset<12>{n};

    return ss.str();
}

// get binary extended
std::string Conversion::displacementExtend(int number)
{

    long long unsigned int n = (number);

    std::stringstream ss;
    ss << std::setw(20) << std::setfill('0') << std::bitset<20>{n};

    return ss.str();
}


std::string Conversion::calculateDisplacement(int binary)
{
    // assume number is already address - pc 


    std::stringstream ss;

    // result to upper case
    ss << std::uppercase << std::hex << binary;

    std::string hexString = ss.str();

    if (hexString.length() >= 3) {
        std::string hexReduced = hexString.substr(hexString.length() - 3);
        return hexReduced;
    } else {
    
        return hexString;
    }

    return "0";

}

std::string Conversion::byteCalc(std::string input)
{
    std::stringstream ss;
    std::string temp = input;
    std::string byte; 


    ss.clear();
    ss.str("");

    for(int i = 0; i < input.size(); i++)
    {
        byte = this->binaryToHex(temp[i]);
        ss << byte;

    }

    return ss.str();
}

std::string Conversion::fillHex(std::string input)
{

    long long unsigned int n = hexToBinary(input);     

    std::stringstream ss;
    std::string temp = input;

    ss.clear();
    ss.str("");

    ss << std::setw(4) << std::setfill('0') << std::left << input;

    return ss.str();

}
