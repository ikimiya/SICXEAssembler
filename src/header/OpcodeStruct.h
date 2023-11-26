#ifndef __OPCODESTRUCT_
#define __OPCODESTRUCT_

#include <string>

struct OpcodeStruct
{
    std::string currentAddr;
    std::string baseAddr;
    std::string pcAddr;
    std::string symAddr;

    std::string label;
    // ADD, SUB etc.
    std::string mnemonic; 
    std::string operand;
    std::string opCode; 
    int format;

    // if opcode does not exist skip generate
    bool skip = false;
    bool indirect = false;
    bool immediate = false;

    std::string byte;

};



#endif // !



