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
    bool firstEnd = true;

    genOp.setSymtable(symTable);

    std::string sendOpcode;
    std::string buffer;
    bool isBuffer = false;
    int format;

    if(symTable.checkTableExist("BASE"))
    {
        baseAddress = symTable.getAddress("BASE");
    } 
    else
    {
        baseAddress = -1;
    }

    // write to file location
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

            // write header
            writeHeader();
            fReader.newLine();
            counter++;

            // read next input line
            readNextInput();
        }   // end if start

        // set length for text record
        textLength = 0;

        // check if control section 
        if(conTab.ifControl())
        {
            isCsect = true;
        }else
        {
            std::string programName = "T"+converter.checkLength(Label);
            std::string startingAddress = "T"+converter.binaryToHexByte(genOp.currentAddr);
            std::string testing = "T" + converter.fillHexNum(Address,6);
            fReader.writeToFileNoTab(testing);
        }

        // keep Read while not end
        while(OpCode != "END")
        {
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
                controlName = Label;

                writeText();
                fReader.newLine();
                writeMod();

                if(firstEnd)
                {
                    writeEnd();
                    firstEnd = false;
                }else
                {
                    fReader.writeToFileNoTab("E");
                    fReader.newLine();
                }

                fReader.newLine();
                writeHeader();
                fReader.newLine();

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
            // csection
            std::string cOperand = Operand + controlName;

            // if it is not comment line 
            if(Label[0] != '.')
            {
                if(OPTABLE.checkOpExist(OpCode))
                {
                    sendOpcode = OPTABLE.getOpcode(OpCode);
                    format = OPTABLE.getFormat(OpCode);

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
                    }   // end while getline

                    // check if not empty
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
                            symbolAddress = "0";
                        }
                    }
                    else
                    {
                        symbolAddress = "0";
                    }   // end if it is not empty
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
                                symbolAddress = converter.intToString(symTable.getAddress(Operand));
                                opStruct.skip = false;

                            }else if(symTable.checkTableExist(tempOperand))
                            {
                                symbolAddress = converter.intToString(symTable.getAddress(tempOperand));

                            }else
                            {   
                                symbolAddress = "0";     
                            }
                    }
                    else
                    {
                        
                    }   // end if not empty
                }
                else if (OpCode == "BYTE" || OpCode == "WORD")
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
                        result = converter.byteCalc(result);
                    }
                    else if (type == "X")
                    {
                        result = (result);
                    }
                    else if (type == "=X")
                    {
                        result = (result);
                    }
                    opStruct.byte = result; 
                    // convert to object code with constants
                }
                else if(OpCode == "EXTDEF")
                {
                    std::istringstream iss(Operand);
                    std::string temp;

                    ssDefine << "D";
                    while(std::getline(iss,temp,','))
                    {
                        externalDef.push_back(temp);
                        if(symTable.checkTableExist(temp))
                        {
                            int number = symTable.getAddress(temp);
                            ssDefine << converter.checkLength(temp) << converter.fillHexNum(number,6);
                            symTable.setDef(temp,1);
                        }
                    }
                    writeDefine();
                    fReader.newLine();
                    symbolAddress = "0";
                }
                else if(OpCode == "EXTREF")
                {
                    std::istringstream iss(Operand);
                    std::string temp;

                    ssRecord << "R";
                    while(std::getline(iss,temp,','))
                    {
                        externalRef.push_back(temp);
                        if(symTable.checkTableExist(temp))
                        {
                            ssRecord << converter.checkLength(temp);
                            symTable.setRef(temp,1);
                        }
                    } 
                    writeRecord();
                    fReader.newLine();
                    symbolAddress = "0";
                    initializeText();
                }
                else
                {
                    opStruct.skip = true;
                }   // end check if exist opcode

                // Literal Table
                if (literalTable.checkTableExist(Operand))
                {
                    symbolAddress = literalTable.getAddress(Operand);

                    // block differenec adding
                    if (symTable.checkTableExist(Operand))
                    {
                        int firstBlock = converter.stringToInt(blockNumber);
                        int secondBlock = symTable.getBlockNumber(Operand);

                        int blockDiff = secondBlock - firstBlock;
                        int newBlock = blockTABLE.getAddressIndex(secondBlock);
                        int currentSymbol = converter.stringToInt(symbolAddress);

                        int finalBlock = newBlock + currentSymbol;

                        symbolAddress = converter.intToString(finalBlock);
                    }
                }   // end if literal table exist

                // Check for block number
                if(blockNumber == "")
                {
                }
                else
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
                        }
                        else
                        {
                        int result = value + symAddr;
                        symbolAddress = converter.intToString(result);
                            if(symTable.checkTableExist(cOperand))
                            {
                                symbolAddress = converter.intToString(symTable.getAddress(cOperand));
                            }
                        }   // end check if literalTable exist
                        
                    } 
                    else if(symTable.checkTableExist(tempOperand))
                    {

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
                        }   // end immediate
                    }
                    else if (isBuffer)
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
                    }   // end symtable exist

                    // means it is not control block
                    if(controlName == firstControl)
                    {

                    }
                    else
                    {
                        if (literalTable.checkTableExist(Operand))
                        {
                            symbolAddress = literalTable.getAddress(Operand);
                        }
                    }    // end control sect

                }   // end check block

                // check for blockNumber difference and add the address to original current addr
                if(blockNumber != "")
                {
                    if(converter.stringToInt(blockNumber) != 0)
                    {
                        int intBlock = converter.stringToInt(blockNumber);
                        currentLoc[counter].second += blockTABLE.getAddressIndex(intBlock);
                    }
                }   // end if not blockNumber

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
                        symbolAddress = "0";
                        opStruct.cSect = true; 
                    }else
                    {
                        opStruct.cSect = false;
                    }
                }   // end symTable

                // check for cs and pblocks
                if(OpCode == "BYTE" || OpCode == "WORD")
                {
                    if(opStruct.cSect)
                    {
                        // if extref 
                        opStruct.byte = "000000";
                    }
                }

                // Set Values to Generate Object Code
                opStruct.currentAddr = converter.intToString(currentLoc[counter].second);
                opStruct.baseAddr = converter.intToString(baseAddress);
                opStruct.pcAddr = converter.intToString(pcLoc[counter].second);
                opStruct.label = Label;
                opStruct.mnemonic = OpCode;
                opStruct.operand = Operand;
                opStruct.opCode = sendOpcode;
                opStruct.format = format;
                opStruct.symAddr = symbolAddress;

                // generate object code
                genOp.setValues(opStruct);
                genOp.checkFormat();
                genOp.createObjectCode();

                // printing object code

                // Modification for cSection
                if(OpCode == "EXTREF" || OpCode == "EXTDEF")
                {
                }
                else
                {
                    if(isCsect)
                    {
                        if(symTable.checkTableExist(value1))
                        {
                            if(symTable.getRef(value1) == 1)
                            {
                                
                                std::string opDisp = converter.opcodeHex(genOp.disp);
                                std::string modification = "+";

                                if(symTable.getRef(value2) == 1 && value2 != "")
                                {   
                                    if(OpCode == "WORD")
                                    {
                                        opDisp = (opStruct.byte);
                                    }
                                    int nextGen = genOp.currentAddr;                
                                    std::string finalText = converter.fillHexNum(nextGen,6) + converter.fillHexNum(opDisp.size(),2);
                                    ssMod << "M" << finalText << modification << value1 << "\n";
                                    ssMod << "M" << finalText << delimiter << value2 << "\n";
                                }
                                else
                                {
                                    int nextGen = genOp.currentAddr + 1;     
                                    std::string finalText = converter.fillHexNum(nextGen,6) + converter.fillHexNum(opDisp.size(),2);
                                    ssMod << "M" << finalText << modification << value1 << "\n";
                                }
                            }
                        }
                    }
                }   // end cModification

                // update object for literalTable
                if(literalTable.checkTableExist(OpCode))
                {
                    genOp.objectCode = literalTable.getOperand(OpCode);
                }

            } // end if not comment

            if(OpCode == "LTORG")
            {
                // "LTORG"
            }
            else
            {
                counter++;
            }

            if(OpCode == "BYTE")
            {
                genOp.objectCode = opStruct.byte;
            }
            
            // Generate Modification Record for nonCsect
            if(genOp.e && symTable.checkTableExist(genOp.operand))
            {
                if(isCsect)
                {

                }
                else
                {
                    int nextGen = genOp.currentAddr + 1;
                    std::string opDisp = converter.opcodeHex(genOp.disp);
                    std::string finalText = converter.fillHexNum(nextGen,6) + converter.fillHexNum(opDisp.size(),2);
                    initializeMod(finalText);
                }
            }   // end noncSect Modification

            // enable to see object code
            //genOp.debug();
            //genOp.checkBits();

            // Resw section
            if(OpCode == "RESW")
            {
                if(genOp.objectCode == "")
                {
                    if(begin)
                    {
                        writeText();
                        fReader.newLine();
                    }
                    begin = false;
                }
            } 
            else if(OpCode == "USE")
            {
                if(genOp.objectCode == "")
                {
                    if(begin)
                    {
                        writeText();
                        fReader.newLine();
                    }
                    begin = false;
                }
            } 
            else
            {
                textLength += genOp.objectCode.size();
                if(genOp.objectCode == "")
                {
                }
                else
                {
                    if(!begin)
                    {
                        begin = true;
                        initializeText();
                    }

                    if(textLength > 60)
                    {
                        textLength -= genOp.objectCode.size();
                        writeText();
                        fReader.newLine();
                        initializeText();
                        writeObjectCode();
                    }
                    else
                    {
                        writeObjectCode();
                    }
                }   // end if not opcode empty
            }   // end if else
            readNextInput();
        }   // end while not end

        // Write Last Text Input
        if(textStarted)
        {
            writeText(); 
            fReader.newLine();
        }else
        {
        }

        // Write Last Modification Record
        writeMod();

        // Write Last End Record
        if(isCsect)
        {
            if(firstEnd)
            {
                writeEnd();
                firstEnd = false;
            }else
            {
                fReader.writeToFileNoTab("E");
            }   // end if is csect
        }
        else
        {
            writeEnd();
        }

    }   // end myfile is open

}   // end pass2

void Pass2::writeHeader()
{
    // Header
    std::string newLabel;
    newLabel = converter.checkLength(Label);
    std::string programName = "H"+newLabel;
    std::string startingAddress = converter.fillHexNum(startAdd,6);
    std::string objectLength = converter.fillHexNum(programLength,6);

    int endAddress = conTab.getEndAddress(controlName);

    if(conTab.checkTableExist(controlName))
    {
        objectLength = converter.fillHexNum(endAddress,6);
    }

    fReader.writeToFileNoTab(programName);
    fReader.writeToFileNoTab(startingAddress);
    fReader.writeToFileNoTab(objectLength);
}

void Pass2::writeText()
{
    int newText = textLength/2;
    std::string objLen = converter.fillHexNum(newText,2);
    std::string finalText = objLen + ssObject.str();

    fReader.writeToFileNoTab(finalText);
    ssObject.str("");
    ssObject.clear();
    textStarted = false;
}

void Pass2::initializeText()
{
    textStarted = true;
    textLength = genOp.objectCode.size();

    std::string programName = "T"+converter.checkLength(Label);
    std::string startingAddress = "T"+converter.binaryToHexByte(genOp.currentAddr);
    std::string testing = "T" + converter.fillHexNum(genOp.currentAddr,6);

    fReader.writeToFileNoTab(testing);
}

void Pass2::writeObjectCode()
{
    ssObject << genOp.objectCode;
}

void Pass2::initializeMod(std::string word)
{
    std::string start = "M"+word;
    ssMod << start << "\n";
}

void Pass2::writeMod()
{
    fReader.writeToFileNoTab(ssMod.str());
    ssMod.str("");
    ssMod.clear();
}

void Pass2::writeEnd()
{
    std::string objectLength = converter.fillHexNum(startAdd,6);
    std::string programName = "E" + objectLength;

    fReader.writeToFileNoTab(programName);
    fReader.newLine();
}

void Pass2::getPassData(int starting, int loc, int pLength)
{
    startAdd = starting;
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

void Pass2::writeRecord()
{
    fReader.writeToFileNoTab(ssRecord.str());
    ssRecord.str("");
    ssRecord.clear();
}

void Pass2::writeDefine()
{
    fReader.writeToFileNoTab(ssDefine.str());
    ssDefine.str("");
    ssDefine.clear();
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

void Pass2::setControlTab(ControlTab cont)
{
    conTab = cont;
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