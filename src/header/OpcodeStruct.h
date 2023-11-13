#ifndef __OPCODESTRUCT_
#define __OPCODESTRUCT_

#include <string>

struct OpcodeStruct
{
    std::string baseAddr;
    std::string pcAddr;
    std::string symAddr;

    std::string label;
    // ADD, SUB etc.
    std::string mnemonic; 
    std::string operand;
    std::string opCode; 
    int format;
};



#endif // !



