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
    //format = format_;
    objectCode = oCode;

    checkFormat();
}

void GenerateOp::checkFormat()
{
    n = 0; i = 0; x = 0; b = 0; p = 0; e = 0;


    bool keepGoing = true;
    int index = 0;

    int pcDisp = 0;
    int baseDisp = 0;


    //  Opcode check [0]
    //  Operand check ,

    if(format == 3)
    {
        n = 1, i = 1;
    } 


    if(mnemonic == "")
    {
        keepGoing == false;
    }

    // Check Opcode
    while(keepGoing)
    {
        // extended
        if(mnemonic.at(index) == '+')
        {
            e = 1;
        }
        index++;
        if(index >= mnemonic.size())
        {
            keepGoing = false;      
        }
    }

    if(operand == "")
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
            if(operand.at(index) == '#')
            {
                i = 1; n = 0;
            }
            // addressing
            if(operand.at(index) == '@')
            {
                i = 0; n = 1;
            }

            if(operand.at(index) == ',')
            {
                x = 1;
                keepGoing = false;
            }

            index++;
            if(index >= operand.size())
            {
                keepGoing = false;        
            }
        }
    }

    // check pc 
    if(operand != "")
    {
        b = 0; p = 1;
    }
    else
    {

    }


    if(format == 1)
    {




    }
    else if (format = 2)
    {

        // check Clear r1,r2
        // clear = B4, a = r1 which a = 0 and if r2 = null/0
        // opcode  = B400 
        // if r2 is empty 0000 -> 0


        // OpCode + R1 + R2

        // check r1, r2

        //objectCode = "Format2"; 
        //std::cout << "AM HERE" << std::endl;



    }
    else if (format = 3)
    {
        if(n == 0 && i == 0)
        {
            n = 1; i = 1;
        }


        pcDisp = symAddr - pcAddr;
        baseDisp = symAddr - baseAddr;

        if(checkPC(pcDisp))
        {
            p = 1; b = 0;


            if(e)
            {
                disp = converter.displacementExtend(pcDisp);
            }
            else
            {
                disp = converter.displacement(pcDisp);
            }


            // any other things
            // generate object code

        }else if (checkBase(baseDisp))
        {
            p = 1; b = 0;

            if(e)
            {
                disp = converter.displacementExtend(pcDisp);
            }
            else
            {
                disp = converter.displacement(pcDisp);
            }

        }else
        {

            std::cout << "Failure, PC: " << pcDisp << " baseDisp: " << baseDisp << std::endl;
            objectCode = "NULL";

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
    // need to check format before doing decimal two/four
    std::string tempCode = converter.decimalToHexTwo(opCode);

    ss.str("");
    ss.clear();

    ss << tempCode << n << i << x << b << p << e << disp;


    // converts 0001 0011 0000 into 130 form
    objectCode = converter.opcodeHex(ss.str());    
    

    if(mnemonic == "BASE")
    {
        objectCode = "";
    }

  

}



void GenerateOp::setValues(OpcodeStruct opStruct)
{
    pcAddr = converter.hexToBinary(opStruct.pcAddr);
    baseAddr = converter.hexToBinary(opStruct.baseAddr);

    // for sym depending on what it is and if symbol exist
    /*
    
        resb resw base start end no opcode
    */

    symAddr = converter.stringToInt(opStruct.symAddr);
    Label = opStruct.label;
    mnemonic = opStruct.mnemonic;
    operand = opStruct.operand;
    opCode = opStruct.opCode; 
    format = opStruct.format;   
}




bool GenerateOp::checkBase(int value)
{
    /*
    1. input is in hex, hexToBinary
    2. int - int for pc
    3. using hex to int find the  borders.
    */
   
    if(0 <= value && 4095 >= value)
    {
        return true;
    }
    return false;
}

bool GenerateOp::checkPC(int value)
{

    if(-2048 <= value && 2047 >= value)
    {
        return true;
    }

    return false;
}

void GenerateOp::debug()
{
    //Checking Values
    std::cout << "PCAddress: [" << pcAddr 
    << "] BaseAddress: [" << baseAddr 
    << "] SymbolAddress: [" << symAddr
    << "] Label: [" << Label 
    << "] Mneomenic: [" << mnemonic
    << "] Operand: [" << operand 
    << "] opCode: [" << opCode 
    << "] Format: [" << format 
    << "] Opcode result: [" << objectCode << "].";
    
}

void GenerateOp::checkBits()
{
    std::cout << "NIXBPE: " << n << i << x << b << p << e << ", "
    << "Displacement: [" << disp << 
    "] ObjectCode " << objectCode << std::endl;
}


