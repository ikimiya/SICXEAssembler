// __GenerateOp.h__
// Generates objectCode


#ifndef __GENERATEOP_H_
#define __GENERATEOP_H_

#include <iostream>
#include <string>
#include <sstream>


class GenerateOp
{
    public:
        GenerateOp();

        ~GenerateOp();


        void setObject(int format, std::string oCode);

        void createObjectCode();

        void checkFormat();

        void setValues(std::string address, std::string label, std::string opCode, std::string Operand);


        bool checkPC();

        bool checkBase();


        void checkBits();



        int format; 
        std::string objectCode;
        std::stringstream ss;


        bool n,i,x,b,p,e;

        std::string Address;
        std::string Label;
        std::string OpCode;
        std::string Operand;

        bool extended;




        /*
        PC = Next

        Base = Base
        
        
        */







};

#endif // !__GENERATEOP_H_