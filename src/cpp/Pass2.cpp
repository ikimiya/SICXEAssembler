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

    //symTable.debug();

    std::string sendOpcode;
    int format;

    if(symTable.checkTableExist("BASE"))
    {
        std::cout << "ExistOP " << std::endl;
        baseAddress = symTable.getAddress("BASE");

    } else
    {
        std::cout << "NotExist " << std::endl;
        
    }

    std::cout << "begin pass2 :" << std::endl;

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



        std::cout << "Address:" << std::endl;

        if(OpCode == "START")
        {
            // write something
            fReader.writeToFile(converter.decimalToHexFour(Address));
            fReader.newLine();

            // read next input line
            readNextInput();

        }   // end if start


        // write header
        writeHeader();
        // initalize text record


        while(OpCode != "END")
        {
            if(OpCode == "BASE")
            {
                baseAddress = symTable.getAddress(Operand);
            } 
            else
            {
                //std::cout << "NotExist " << std::endl;
            }


            

            // if it is not comment line 
            if(Label[0] != '.')
            {
                // search table for op code
                // also check without special + 

                std::string eCode = OpCode;
                eCode.erase(0,1);
                std::string tempOperand = Operand;
                tempOperand.erase(0,1);

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
                        }else if (!keepGoing)
                        {
                            value2 = tempOp;
                            indexMode = true;
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

                    // convert to object code with constants
                }else
                {
                    //std::cout << "Does Not Exist: " << OpCode << std::endl;
                    opStruct.skip = true;
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
                
                opStruct.baseAddr = converter.intToString(baseAddress);
                opStruct.pcAddr = Address;
                opStruct.label = Label;
                opStruct.mnemonic = OpCode;
                opStruct.operand = Operand;
                opStruct.opCode = sendOpcode;
                opStruct.format = format;
                opStruct.symAddr = symbolAddress;


                //std::cout << "CHECKBASE: " << opStruct.baseAddr << std::endl;
                


                //std::cout << "pc Address: " << opStruct.pcAddr << std::endl

                

                
                //if(opStruct.operand != "LENGTHh" && opStruct.mnemonic != "BASEj")
                //{
                    genOp.setValues(opStruct);
                    genOp.checkFormat();
                    genOp.createObjectCode();
                    genOp.debug();
                    genOp.checkBits();
                //}

                





        



                //std::cout << "PCAddress: " << Address << " BaseAddress: " << baseAddress << " Label: " << Label << " OpCode: " << OpCode << " Operand: " << Operand;
                //std::cout << "Format: " << format << " OPCODE: " << sendOpcode << std::endl;

                

                //genOp.setValues(Address, Address, Label, OpCode, Operand);



                //genOp.debug();

                //std::cout << "erro    r " << std::endl;

            } // end if not comment


            /*
                Write listening line 
            */
           readNextInput();






        }   // end while nmot end 

        // write text to Text object program

        // write end record 

        //write last listing line




    }   // end myfile is open

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

}


void Pass2::setOptable(Optable op)
{
    OPTABLE = op;
}

void Pass2::setSymtable(Symtable sym)
{
    symTable = sym;
}