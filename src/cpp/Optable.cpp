// __Optable.cpp__

#include "../header/Optable.h"
#include <map>

Optable::Optable()
{

}

Optable::~Optable()
{

}

void Optable::createTable()
{
    /*Mnemonic, format, opcode
        Assume format 3 is 3/4 which will test in code
    */
    OPTABLE["ADD"] = std::make_pair(3, "18");
    OPTABLE["ADDF"] = std::make_pair(3, "58");
    OPTABLE["ADDR"] = std::make_pair(2, "90");
    OPTABLE["AND"] = std::make_pair(3, "40");
    OPTABLE["CLEAR"] = std::make_pair(2, "B4");
    OPTABLE["COMP"] = std::make_pair(3, "28");
    OPTABLE["COMPF"] = std::make_pair(3, "88");
    OPTABLE["COMPR"] = std::make_pair(2, "A0");
    OPTABLE["DIV"] = std::make_pair(3, "24");
    OPTABLE["DIVF"] = std::make_pair(3, "64");
    OPTABLE["DIVR"] = std::make_pair(2, "9C");
    OPTABLE["FIX"] = std::make_pair(1, "C4");
    OPTABLE["FLOAT"] = std::make_pair(1, "C0");
    OPTABLE["HIO"] = std::make_pair(1, "F4");
    OPTABLE["J"] = std::make_pair(3, "3C");
    OPTABLE["JEQ"] = std::make_pair(3, "30");
    OPTABLE["JGT"] = std::make_pair(3, "34");
    OPTABLE["JLT"] = std::make_pair(3, "38");
    OPTABLE["JSUB"] = std::make_pair(3, "48");
    OPTABLE["LDA"] = std::make_pair(3, "00");
    OPTABLE["LDB"] = std::make_pair(3, "68");
    OPTABLE["LDCH"] = std::make_pair(3, "50");
    OPTABLE["LDF"] = std::make_pair(3, "70");
    OPTABLE["LDL"] = std::make_pair(3, "08");
    OPTABLE["LDS"] = std::make_pair(3, "6C");
    OPTABLE["LDT"] = std::make_pair(3, "74");
    OPTABLE["LDX"] = std::make_pair(3, "04");
    OPTABLE["LPS"] = std::make_pair(3, "D0");
    OPTABLE["MUL"] = std::make_pair(3, "20");
    OPTABLE["MULF"] = std::make_pair(3, "60");
    OPTABLE["MULR"] = std::make_pair(2, "98");
    OPTABLE["NORM"] = std::make_pair(1, "C8");
    OPTABLE["OR"] = std::make_pair(3, "44");
    OPTABLE["RD"] = std::make_pair(3, "D8");
    OPTABLE["RMO"] = std::make_pair(2, "AC");
    OPTABLE["RSUB"] = std::make_pair(3, "4C");
    OPTABLE["SHIFTL"] = std::make_pair(2, "A4");
    OPTABLE["SHIFTR"] = std::make_pair(2, "A8");
    OPTABLE["SIO"] = std::make_pair(1, "F0");
    OPTABLE["SSK"] = std::make_pair(3, "EC");
    OPTABLE["STA"] = std::make_pair(3, "0C");
    OPTABLE["STB"] = std::make_pair(3, "78");
    OPTABLE["STCH"] = std::make_pair(3, "54");
    OPTABLE["STF"] = std::make_pair(3, "80");
    OPTABLE["STI"] = std::make_pair(3, "D4");
    OPTABLE["STL"] = std::make_pair(3, "14");
    OPTABLE["STS"] = std::make_pair(3, "7C");
    OPTABLE["STSW"] = std::make_pair(3, "E8");
    OPTABLE["STT"] = std::make_pair(3, "84");
    OPTABLE["STX"] = std::make_pair(3, "10");
    OPTABLE["SUB"] = std::make_pair(3, "1C");
    OPTABLE["SUBF"] = std::make_pair(3, "5C");
    OPTABLE["SUBR"] = std::make_pair(2, "94");
    OPTABLE["SVC"] = std::make_pair(2, "B0");
    OPTABLE["TD"] = std::make_pair(3, "E0");
    OPTABLE["TIO"] = std::make_pair(1, "F8");
    OPTABLE["TIX"] = std::make_pair(3, "2C");
    OPTABLE["TIXR"] = std::make_pair(2, "B8");
    OPTABLE["WD"] = std::make_pair(3, "DC");
}

int Optable::getFormat(std::string Mnemonic)
{
    return OPTABLE[Mnemonic].first;
}

std::string Optable::getOpcode(std::string Mnemonic)
{
    return OPTABLE[Mnemonic].second;;
}

bool Optable::checkOpExist(std::string Mnemonic)
{
    bool exist = false; 
    
    if(OPTABLE.find(Mnemonic) == OPTABLE.end())
    {
        return false;
    }
    else
    {
        return true;
    }
    return false;
}

// debug the code
void Optable::debug()
{
    for(auto it = OPTABLE.begin(); it != OPTABLE.end(); it++)
    {
        /*
        std::string mnemonic = it->first;
        int format = it->second.first;
        std::string opcode = it->second.second;
        */
        std::string mnemonic = it->first;
        int format = getFormat(mnemonic);
        std::string opcode = getOpcode(mnemonic);
        std::cout << "Mnemonic: " << mnemonic << 
                    ", Format: " << format << 
                    ", Opcode: " << opcode << std::endl;

    }
}