// __GenerateOp.h__
// Generates objectCode


#ifndef __GENERATEOP_H_
#define __GENERATEOP_H_

#include <iostream>
#include <string>
#include <sstream>
#include "../header/OpcodeStruct.h"
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
        std::string Label;
        std::string mnemonic;
        std::string operand;
        std::string opCode;
        int format;

        bool extended;


        Conversion converter;

        /*
        PC = Next

        Base = Base
        
        
        */







};

#endif // !__GENERATEOP_H_