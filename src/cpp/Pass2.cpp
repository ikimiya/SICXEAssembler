// __Pass2.cpp__

#include "../header/Pass2.h"


Pass2::Pass2()
{

}

Pass2::~Pass2()
{

}

void Pass2::setFileName(std::string fileName_)
{
    fileName = fileName_;
    fReader.readFile("Immediate/" + fileName + "testIMT.txt");

}

void Pass2::beginPass2()
{
    int baseAddress = -1;


    genOp.setSymtable(symTable);
    //genOp.setLiteral(litTable);

    //symTable.debug();
    blockTABLE.debug();
    literalTable.debug();


    //std::cout << "BlockTable Index at 0 :" << blockTABLE.getAddressIndex(3) << std::endl;

    std::string sendOpcode;
    std::string buffer;
    bool isBuffer = false;
    int format;

    if(symTable.checkTableExist("BASE"))
    {
        std::cout << "ExistOP " << std::endl;
        baseAddress = symTable.getAddress("BASE");

    } else
    {
        std::cout << "NotExist " << std::endl;
        baseAddress = -1;
        
    }


    fReader.writeFile("Result/" + fileName + "result.txt");

    if(fReader.myFile.is_open())
    {
        // get first line from intermediate
        std::getline(fReader.myFile,currentLine);
        ss << currentLine;

        std::getline(ss, Address, '\t');
        std::getline(ss, Label, '\t');
        std::getline(ss, OpCode, '\t');
        std::getline(ss, Operand, '\t');
        std::getline(ss, blockNumber, '\t');

        if(OpCode == "START")
        {

            controlName = Label;
            firstControl = Label;
            // write something
            fReader.writeToFile(converter.decimalToHexFour(Address));
            fReader.newLine();

            counter++;
            // read next input line
            readNextInput();


        }   // end if start


        //std::cout << "Pass 2 Address Start 2" << std::endl;


        // write header
        writeHeader();
        // initalize text record

        //counter++;


        while(OpCode != "END")
        {

            //std::cout << "Input: ";
            //debug();
            opStruct.cSect = false;

            std::string eCode = OpCode;
            eCode.erase(0,1);
            std::string tempOperand = Operand;
            tempOperand.erase(0,1);
            buffer = "";

            if(OpCode == "BASE")
            {
                baseAddress = symTable.getAddress(Operand);
            } 
            else if(OpCode == "CSECT")
            {
                std::cout << "CSECT RESET VECTORS " << std::endl;

                controlName = Label;

                // set External Ref to zero
                for(auto it = externalRef.begin(); it != externalRef.end(); it++)
                {
                    if(symTable.checkTableExist(*it))
                    {
                        symTable.setRef(*it,0);
                    }
                }

                for(auto it = externalDef.begin(); it != externalDef.end(); it++)
                {
                    if(symTable.checkTableExist(*it))
                    {
                        symTable.setDef(*it,0);
                    }
                }

                externalDef.clear();
                externalRef.clear();

            }

            std::string cOperand = Operand + controlName;

        

            // if it is not comment line 
            if(Label[0] != '.')
            {

                //std::cout << controlName << std::endl;
                // search table for op code
                // also check without special + 

                //std::cout << "check Operand: " << tempOperand << std::endl;

                if(OPTABLE.checkOpExist(OpCode))
                {
                    sendOpcode = OPTABLE.getOpcode(OpCode);
                    format = OPTABLE.getFormat(OpCode);
                    //std::cout << "Operand: " << Operand << std::endl;

                    std::istringstream iss(Operand);
                    std::string tempOp;
                    std::string result2;
                    bool indexMode = false;
                    bool keepGoing = true;
                    std::string value1 = "";
                    std::string value2 = "";
                    while(std::getline(iss,tempOp,','))
                    {
                        if(keepGoing)
                        {
                            value1 = tempOp;
                            buffer = tempOp;
                
                        }else if (!keepGoing)
                        {
                            value2 = tempOp;
                            indexMode = true;
                            isBuffer = true;
                        }
                        keepGoing = false;
                    }

                    if(Operand != "")
                    {
                        // need to check fo @ # etc.
                        
                        if(symTable.checkTableExist(Operand))
                        {
                            //std::cout << "testing: Duplicated Symbol Found" << std::endl;
                            symbolAddress = converter.intToString(symTable.getAddress(Operand));


                            if(symTable.checkTableExist(cOperand))
                            {
                                symbolAddress = converter.intToString(symTable.getAddress(cOperand));
                            }

                            opStruct.skip = false;
                        }
                        else if(symTable.checkTableExist(tempOperand))
                        {
                            symbolAddress = converter.intToString(symTable.getAddress(tempOperand));
                        }
                        else if(indexMode)
                        {
                            //std::cout << "INDEX MODE!!" << std::endl;
                            //std::cout << "BUFFER:" << value1 << std::endl;
                            if(symTable.checkTableExist(value1))
                            {
                                symbolAddress = converter.intToString(symTable.getAddress(value1));
                            }
                            else
                            {
                                symbolAddress = "0";
                            }
                        }
                        else
                        {   
                            //std::cout << "Operand Checking: " << Operand << std::endl;
                            symbolAddress = "0";
                            //std::cout << "Set Error Flag Undefined Symbol" << std::endl;         
                        }
                            
                    }
                    else
                    {
                        symbolAddress = "0";
                    }
                }
                else if (OPTABLE.checkOpExist(eCode))
                {
                    sendOpcode = OPTABLE.getOpcode(eCode);
                    format = OPTABLE.getFormat(eCode);
                    if(Operand != "")
                        {
                            // need to check fo @ # etc.
                            if(symTable.checkTableExist(Operand))
                            {
                                //std::cout << "testing: Duplicated Symbol Found" << std::endl;
                                symbolAddress = converter.intToString(symTable.getAddress(Operand));
                                opStruct.skip = false;

                            }else if(symTable.checkTableExist(tempOperand))
                            {
                                symbolAddress = converter.intToString(symTable.getAddress(tempOperand));

                            }else
                            {   
                                symbolAddress = "0";
                                //std::cout << "Set Error Flag Undefined Symbol" << std::endl;         
                            }
                    }else
                    {
                        
                    }
                    // end if symbol
                    // calculate Object code
                    
                }else if (OpCode == "BYTE" || OpCode == "WORD")
                {

                    std::istringstream iss(Operand);
                    std::string temp;
                    std::string result;
                    std::string type;

                    int byte;
                    while(std::getline(iss,temp,'\''))
                    {
                        if(temp != "C" || temp != "X" || temp != "=X")
                        {
                            result = temp;
                        }
                        if(temp == "C" || temp == "X" || temp == "=X")
                        {
                            type = temp;
                        }
                    }

                    if(type == "C")
                    {
                        //std::cout << "ResultC" << result << std::endl;
                        result = converter.byteCalc(result);
                    }
                    else if (type == "X")
                    {
                        //std::cout << "ResultX" << result << std::endl;
                        result = (result);
                        
                    }
                    else if (type == "=X")
                    {
                        //std::cout << "Result=X" << result << std::endl;
                        result = (result);
                    }
                    opStruct.byte = result; 
                    //std::cout << "byte check: " << result << std::endl;

                    // convert to object code with constants
                }
                else if(OpCode == "EXTDEF")
                {
                    std::istringstream iss(Operand);
                    std::string temp;

                    while(std::getline(iss,temp,','))
                    {

                        std::cout << "extDef: " << temp << std::endl;
                        externalDef.push_back(temp);
                        if(symTable.checkTableExist(temp))
                        {
                            symTable.setDef(temp,1);
                        }
                    }
                    symbolAddress = "0";
                }
                else if(OpCode == "EXTREF")
                {
                    std::istringstream iss(Operand);
                    std::string temp;
                    
                    while(std::getline(iss,temp,','))
                    {

                        std::cout << "ExtRef: " << temp << std::endl;
                        externalRef.push_back(temp);
                        if(symTable.checkTableExist(temp))
                        {
                            symTable.setRef(temp,1);
                        }
                    }
                    symbolAddress = "0";
                }else
                {
                    //std::cout << "Does Not Exist: " << OpCode << std::endl;
                    opStruct.skip = true;
                }

                // Literal Table


                if (literalTable.checkTableExist(Operand))
                {
                    symbolAddress = literalTable.getAddress(Operand);
                    //std::cout << literalTable.getOperand(OpCode) << std::endl;
                }

                

                // BlocKNumber
                if(blockNumber == "")
                {
                }else
                {
                    if(symTable.checkTableExist(Operand) || literalTable.checkTableExist(Operand))
                    {
                        int blockNum = converter.stringToInt(blockNumber);
                        int symNumber = symTable.getBlockNumber(Operand);
                        int value = symTable.getAddress(Operand);
                        int symAddr = blockTABLE.getAddressIndex(symNumber);


                        if (literalTable.checkTableExist(Operand))
                        {
                            value = converter.stringToInt(literalTable.getAddress(Operand));
                            //std::cout << "Operand" << Operand << " Value: " << value  << "sym: " << symAddr<< std::endl;
                        }

                        // std::cout << symAddr << std::end;;

                        int result = value + symAddr;

                        //std::cout << "result is " << result << std::endl;



                        symbolAddress = converter.intToString(result);
                        if(symTable.checkTableExist(cOperand))
                        {
                            symbolAddress = converter.intToString(symTable.getAddress(cOperand));
                        }

                        
                    } 
                    else if(symTable.checkTableExist(tempOperand))
                    {
                        //std::cout << "temp Operand" << tempOperand << std::endl;

                        if(Operand[0] == '#')
                        {

                        }
                        else
                        {
                            int blockNum = converter.stringToInt(blockNumber);


                            int symNumber = symTable.getBlockNumber(tempOperand);
                            int value = symTable.getAddress(tempOperand);
                            int symAddr = blockTABLE.getAddressIndex(symNumber);

                            if (literalTable.checkTableExist(tempOperand))
                            {
                                value = converter.stringToInt(literalTable.getAddress(tempOperand));
                            }

                            int result = value + symAddr;

                            symbolAddress = converter.intToString(result);

                        }
                    }else if (isBuffer)
                    {

                            int blockNum = converter.stringToInt(blockNumber);
                            int symNumber = symTable.getBlockNumber(buffer);
                            int value = symTable.getAddress(buffer);
                            int symAddr = blockTABLE.getAddressIndex(symNumber);

                            int result = value + symAddr;
                            symbolAddress = converter.intToString(result);


                        isBuffer = false;
                    }
                    else
                    {
                        isBuffer = false;
                    }

                    // means it is not control block
                    if(controlName == firstControl)
                    {

                    }
                    else
                    {
                        if (literalTable.checkTableExist(Operand))
                        {
                            symbolAddress = literalTable.getAddress(Operand);
                            //std::cout << literalTable.getOperand(OpCode) << std::endl;
                        }
                    }

                }



                // control section check
                std::istringstream iss(Operand);
                std::string temp;
                std::string value1;
                std::string value2;
                std::string delimiter;
                int byte;
                bool keepGoing = true;

                for(int i = 0; i < Operand.size(); i++)
                {
                    if(Operand[i] == '+' || Operand[i] == '-' || Operand[i] == '*' || Operand[i] == '/' || Operand[i] == ',')
                    {
                        delimiter = Operand[i];
                        keepGoing = false;
                    }
                    else if(keepGoing)
                    {
                        value1 += Operand[i];
                    }
                    else
                    {
                        value2 += Operand[i];
                    }
                }

                if(symTable.checkTableExist(value1))
                {
                    if(symTable.getRef(value1))
                    {
                        //std::cout << "External Ref: [" << Operand << "]" << symTable.getRef(value1) <<std::endl;
                        symbolAddress = "0";
                        opStruct.cSect = true; 
                    }else
                    {
                        opStruct.cSect = false;

                    }
                }

                // check for cs
                if(OpCode == "BYTE" || OpCode == "WORD")
                {
                    if(opStruct.cSect)
                    {
                        // if extref 
                        opStruct.byte = "000000";
                    }

                }



                /*
                // check code counter
                if object code is >= 10 * 3, 
                    create new text record
                else
                add object cord to text record

                */
                //std::cout << "error " << std::endl;
                //std::string baseAddress = converter.intToString(symTable.getAddress("BASE"));

                //std::cout << "Operand: " << Operand << " SYMBOL: " <<  symbolAddress << std::endl;
            
                //std::cout << "Pass 2 Address Start 2" << std::endl;
                
                opStruct.currentAddr = converter.intToString(currentLoc[counter].second);
                opStruct.baseAddr = converter.intToString(baseAddress);
                opStruct.pcAddr = converter.intToString(pcLoc[counter].second);
                opStruct.label = Label;
                opStruct.mnemonic = OpCode;
                opStruct.operand = Operand;
                opStruct.opCode = sendOpcode;
                opStruct.format = format;
                opStruct.symAddr = symbolAddress;

                //std::cout << "CHECKBASE: " << opStruct.baseAddr << std::endl

                //std::cout << "pc Address: " << opStruct.pcAddr << std::endl

            //if(opStruct.operand == "MAXLEN")
            // {
                genOp.setValues(opStruct);
                genOp.checkFormat();
                genOp.createObjectCode();
                genOp.debug();
                genOp.checkBits();
            // }

            

            //std::cout << "Pass 2 Address Start 3" << std::endl;

            } // end if not comment

            if(OpCode == "LTORG")
            {
                std::cout << "CHECK: LTORG " << std::endl;
                //std::cout << "Operand: " << literalTable.getOperand(Operand) << std::endl;
            }
            else
            {
                counter++;
            }

            readNextInput();


        }   // end while nmot end 




        // write text to Text object program

        // write end record 

        //write last listing line



    }   // end myfile is open





    //symTable.debug();


}

void Pass2::writeHeader()
{
    // Need to check Label length of 6
    std::string programName = "H"+Label;
    std::string startingAddress = "00"+converter.binaryToHexByte(startAdd);
    std::string objectLength = "00"+converter.binaryToHexByte(programLength);

    fReader.writeToFile(programName);
    fReader.writeToFileNoTab(startingAddress);
    fReader.writeToFileNoTab(objectLength);
    fReader.newLine();

}

void Pass2::getPassData(int starting, int loc, int pLength)
{
    startAdd = startAdd;
    //LocCtr = loc;
    programLength = pLength;
}

void Pass2::readNextInput()
{

    std::getline(fReader.myFile,currentLine);
    ss.clear();
    ss.str(std::string());
    ss << currentLine;
    std::getline(ss, Address, '\t');
    std::getline(ss, Label, '\t');
    std::getline(ss, OpCode, '\t');
    std::getline(ss, Operand, '\t');
    std::getline(ss, blockNumber, '\t');


}

void Pass2::setOptable(Optable op)
{
    OPTABLE = op;
}

void Pass2::setSymtable(Symtable sym)
{
    symTable = sym;
}

void Pass2::setLiteralTab(Libtab lib)
{
    literalTable = lib;
}

void Pass2::setLocation(std::vector<std::pair<int,int>> curLoc, std::vector<std::pair<int,int>> nexLoc)
{
    currentLoc = curLoc;
    pcLoc = nexLoc;
}
void Pass2::setBlockTab(BlockTable bloc)
{
    blockTABLE = bloc;
}

void Pass2::debug()
{

    std::cout 
    << "Address: [" << Address
    << "] Label: [" << Label 
    << "] OpCode: [" << OpCode
    << "] Operand: [" << Operand
    << "] blockNumber: [" << Address << "]. " << std::endl;
}