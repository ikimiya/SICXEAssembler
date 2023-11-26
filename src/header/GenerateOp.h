// __GenerateOp.h__
// Generates objectCode


#ifndef __GENERATEOP_H_
#define __GENERATEOP_H_

#include <iostream>
#include <string>
#include <sstream>
#include "../header/OpcodeStruct.h"
#include "../header/Symtable.h"


#include "../../Math/Conversion.h"

class GenerateOp
{
    public:
        GenerateOp();

        ~GenerateOp();

        void setObject(int format, std::string oCode);

        void createObjectCode();

        void checkFormat();


        void setValues(OpcodeStruct opStruct);

        bool checkPC(int value);

        bool checkBase(int value);


        void checkBits();

        void debug();


        void setSymtable(Symtable sym);

        Symtable symTable;

        OpcodeStruct opStruct;

        std::string objectCode;
        std::stringstream ss;


        bool n,i,x,b,p,e;

        std::string disp;

        std::string Address;


        // use for transition
        int pcAddr;
        int baseAddr;
        int symAddr;
        int currentAddr;
        std::string Label;
        std::string mnemonic;
        std::string operand;
        std::string opCode;
        std::string resultByte;
        int format;
        bool skip;

        Conversion converter;

        /*
        PC = Next

        Base = Base
        
        
        */







};

#endif // !__GENERATEOP_H_