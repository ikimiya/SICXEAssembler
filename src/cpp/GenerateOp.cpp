// __GenerateOp.cpp

#include "../header/GenerateOp.h"


GenerateOp::GenerateOp()
{

}


GenerateOp::~GenerateOp()
{

}

void GenerateOp::setObject(int format_, std::string oCode)
{
    format = format_;
    objectCode = oCode;

    checkFormat();

}

void GenerateOp::checkFormat()
{

    bool keepGoing = true;
    int index = 0;

    //  Opcode check [0]
    //  Operand check ,

    if(format == 3)
    {
        n = 1, i = 1;
    } 

    // Check Opcode
    while(keepGoing)
    {
        // extended
        if(OpCode.at(index) == '+')
        {
            e = 1;
        }
        index++;
        if(index >= OpCode.size())
        {
            keepGoing = false;      
        }
    }

    if(Operand == "")
    {
        x = 0;
        b = 0;
        p = 0;
        e = 0;
    }
    else
    {
        keepGoing = true;
        index = 0;
        while(keepGoing)
        {
            // immediate
            if(Operand.at(index) == '#')
            {
                i = 1; n = 0;
            }
            // addressing
            if(Operand.at(index) == '@')
            {
                i = 0; n = 1;
            }

            if(Operand.at(index) == ',')
            {
                x = 1;
                keepGoing = false;
            }

            index++;
            if(index >= Operand.size())
            {
                keepGoing = false;        
            }
        }
    }

    // check pc 
    if(Operand != "")
    {
        b = 0; p = 1;
    }
    else
    {

    }


    if(format = 1)
    {




    }else if (format = 2)
    {

        // check Clear r1,r2
        // clear = B4, a = r1 which a = 0 and if r2 = null/0
        // opcode  = B400 
        // if r2 is empty 0000 -> 0


        // OpCode + R1 + R2

        // check r1, r2



    }
    else if (format = 3)
    {
        if(n == 0 && i == 0)
        {
            n = 1; i = 1;
        }
        
        // if + = extended 
        // check if extended = true

    }


    // check bits

    /*
    

    @ = n = 1, i = 0
    # = n = 0, i = 1
    else n = 1, i = 1
    if + then e = 1
    if there is ,X then x = 1

    PC
    1. Check pc after formula range

    2. check B after formula range    
    
    */

}

void GenerateOp::createObjectCode()
{


    

}

void GenerateOp::setValues(std::string address_, std::string bAddress_,std::string label_, std::string opcode_, std::string operand_)
{
    Address = address_;
    baseAddress = bAddress_;
    Label = label_;
    OpCode = opcode_;
    Operand = operand_;
}

void GenerateOp::checkBits()
{
    std::cout << "NIXBPE" << std::endl;
    std::cout << n << i << x << b << p << e << std::endl;
}


bool GenerateOp::checkBase()
{


    return false;
}


bool GenerateOp::checkPC()
{

    return false;
}

void GenerateOp::debug()
{

    std::cout << "PCAddress: " << Address << " BaseAddress: " <<
    baseAddress << "Label: " << Label << " Opcode: " << OpCode
    << " Operand: " << Operand << std::endl;   



}