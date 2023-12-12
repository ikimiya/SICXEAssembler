// __GenerateOp.cpp

#include "../header/GenerateOp.h"


GenerateOp::GenerateOp()
{

}


GenerateOp::~GenerateOp()
{

}

void GenerateOp::checkFormat()
{
    if(cSect)
    {

    }
    if(skip)
    {

    }
    else if (mnemonic == "BYTE" || mnemonic == "WORD")
    {

    }
    else{
        n = 0; i = 0; x = 0; b = 0; p = 0; e = 0;

        bool keepGoing = true;
        int index = 0;

        int pcDisp = 0;
        int baseDisp = 0;
        disp = "";

        bool immediate = false;
        bool extended = false;
        bool indirect = false; 

        //  Opcode check [0]
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
                extended = true;
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
            disp = converter.displacement(0);
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
                    immediate = true;
                }
                // addressing
                if(operand.at(index) == '@')
                {
                    i = 0; n = 1;
                    indirect = true;
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
        else if (format == 2)
        {

            if(operand.size() > 1)
            {
                std::istringstream iss(operand);
                std::string tempOp;
                bool keepGoing = true;

                std::string value1 = "";
                std::string value2 = "";
                while(std::getline(iss,tempOp,','))
                {
                    if(keepGoing)
                    {
                        value1 = tempOp;
                    }else if (!keepGoing)
                    {
                        value2 = tempOp;
                    }
                    keepGoing = false;
                }
                
                std::stringstream ss;
                ss.clear();
                ss.str("");

                ss << std::uppercase << opCode;
                if(symTable.checkTableExist(value1))
                {
                    int tempValue = symTable.getAddress(value1);
                    ss << tempValue;
                }

                if(symTable.checkTableExist(value2))
                {
                    int tempValue = symTable.getAddress(value2);
                    ss << tempValue;
                }

                objectCode = converter.fillHex(ss.str());
            }
            else
            {
                std::istringstream iss(operand);
                std::string tempOp;
                bool keepGoing = true;
                std::string value1 = operand;

                std::stringstream ss;

                ss.clear();
                ss.str("");
                ss << std::uppercase << opCode;

                if(symTable.checkTableExist(value1))
                {
                    int tempValue = symTable.getAddress(value1);
                    ss << tempValue;

                }

                objectCode = converter.fillHex(ss.str());
            }
        }
        else if (format == 3)
        {
            // calculate Displacement for Base
            pcDisp = symAddr - pcAddr;
            baseDisp = symAddr - baseAddr;


            if(n == 0 && i == 0)
            {
                
                n = 1; 
                i = 1;
            }
        

            if(operand == "")
            {
                p = 0;
                b = 0;
            }else if(e == 1 && symAddr != 0)
            {
                p = 0; b = 0;
                disp = converter.displacementExtend(symAddr);
            }
            else if(n == 0 && i == 1 && symAddr == 0 && e != 1)
            {
                
                p = 0; b = 0;
                std::string temp = operand;
                temp.erase(0,1);
                int iAdd = converter.stringToInt(temp);

                disp = converter.displacement(iAdd);
            }
            else if(n == 0 && i == 1 && symAddr == 0 && e == 1)
            {
                
                
                p = 0; b = 0;
                std::string temp = operand;
                temp.erase(0,1);
                int iAdd = converter.stringToInt(temp);
                disp = converter.displacementExtend(iAdd);  
            }
            else if(checkPC(pcDisp))
            {
                if(e == 1)
                {
                    p = 0; b = 0;
                    if(cSect)
                    {
                        disp = converter.displacementExtend(symAddr);
                    }
                    else
                    {
                        disp = converter.displacementExtend(pcDisp);
                    }
                } else if (n == 0 && i == 1)
                {

                    
                    p = 1; b = 0;
                    disp = converter.displacement(pcDisp);
                }
                else if (n == 1 && i == 0)
                {

                    
                    p = 1; b = 0;
                    disp = converter.displacement(pcDisp);
                }
                else
                {

                    
                    p = 1; b = 0;
                    disp = converter.displacement(pcDisp);
                }
                // generate object code

            }else if (checkBase(baseDisp))
            {
                p = 0; b = 1;

                if(e)
                {
                    disp = converter.displacementExtend(baseDisp);
                }
                else
                {
                    disp = converter.displacement(baseDisp);
                }
            }
            else
            {
                //std::cout << "Failure, PC: " << pcDisp << " baseDisp: " << baseDisp << std::endl;
                //objectCode = "NULL";
            }
        }
    }
}

void GenerateOp::createObjectCode()
{
    // need to check format before doing decimal two/four
    if(skip)
    {
        objectCode = "";
    }
    else if (mnemonic == "BYTE" || mnemonic == "WORD")
    {
        objectCode = resultByte;
    }
    else
    {
        if(format == 3)
        {
            std::string tempCode;
            std::stringstream operandCode;
            if(e)
            {

            }
            else
            {

            }
            tempCode = converter.decimalToHexTwo(opCode);
            operandCode << tempCode << n << i << x << b << p << e << disp;
            std::string code = converter.opcodeHex(operandCode.str());
            objectCode = converter.opcodeHex(operandCode.str());    
        }
    }
}

void GenerateOp::setValues(OpcodeStruct opStruct)
{
    // set Values to Compute object code
    currentAddr = converter.stringToInt(opStruct.currentAddr);
    pcAddr = converter.stringToInt(opStruct.pcAddr);
    baseAddr = converter.stringToInt(opStruct.baseAddr);
    symAddr = converter.stringToInt(opStruct.symAddr);
    Label = opStruct.label;
    mnemonic = opStruct.mnemonic;
    operand = opStruct.operand;
    opCode = opStruct.opCode; 
    format = opStruct.format;   
    skip = opStruct.skip;
    resultByte = opStruct.byte;
    cSect = opStruct.cSect;
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
    std::cout 
    
    << "CurrentAddr: [" << converter.binaryToHex(currentAddr) 
    << "] PCAddress: [" << converter.binaryToHex(pcAddr) 
    << "] BaseAddress: [" << converter.binaryToHex(baseAddr) 
    << "] SymbolAddress: [" << converter.binaryToHex(symAddr) 
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
    "] ObjectCode: [" << objectCode << "]" << std::endl;
}

void GenerateOp::setSymtable(Symtable sym)
{
    this->symTable = sym;
}


