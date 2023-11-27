// __Pass1.cpp__

#include "../header/Pass1.h"

#include <algorithm>

Pass1::Pass1()
{
    OPTABLE.createTable();
}

Pass1::~Pass1()
{

}

void Pass1::setFileName(std::string fileName_)
{
    fileName = fileName_;
    fReader.readFile("Input/" + fileName + ".txt");

}

/// @brief 
void Pass1::beginPass1()
{

    // LOCCTR, Label, Opcode, Operand || ignore comment line
    fReader.writeFile("Immediate/" + fileName + "testIMT.txt");

    errorF = false;
    symbolF = false;


    if (fReader.myFile.is_open()) {
        //while (std::getline(fReader.myFile,currentLine)) {  

            // default block
            blockTABLE.bTable.address = 0;
            blockTABLE.bTable.length = 0;
            blockTABLE.bTable.blockNumber = blockCounter;
            blockName = "DEFAULT";
            blockTABLE.insertTable(blockName,blockTABLE.bTable);

            std::getline(fReader.myFile,currentLine);
            // use ss to get the current line
            ss << currentLine;
            // get       Label, OpCode, Operand .ignore split by tab
            // fucntions COPY   START   0       COMMENT
            std::getline(ss, Label, '\t');
            std::getline(ss, OpCode, '\t');
            std::getline(ss, Operand, '\t');
            std::getline(ss, Comment, '\t');

            if(OpCode == "START")
            {
                // save #operand as starting address 
                startAdd = converter.stringToInt(Operand);

                // convert locctr to int
                LocCtr = converter.stringToInt(Operand);

                //std::cout << "LOC: " << LocCtr << std::endl;


                // write to Line imemdiate file
                std::cout << "beginning line: ";
                std::cout  << "[Loc:" << LocCtr << "] [Label:" << Label << "] [OPcode:" << OpCode << "] [Operand:" << Operand << "]" << std::endl;

                fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
                //fReader.writeToFile(converter.intToString(errorF));
                //fReader.writeToFile(converter.intToString(symbolF));
                fReader.newLine();

                readNextInput();
                
            }// end if start
            else{
                LocCtr = 0;
            }   


            currentLoc.push_back({counter,LocCtr});
            pcLoc.push_back({counter,LocCtr});
            counter++;

            while(OpCode != "END")
                {

                    if(OpCode == "USE")
                    {
                        // if empty it is default block

                        std::cout << "currentBlockName" << blockName << std::endl;
                        if(Operand == "")
                        {
                            //std::cout << "Changing TO DEfault block" << std::endl;
                            /*
                            change loc, block name, block number to it
                            */
                           
                            // this sets the last locctr to block name
                            blockTABLE.setLength(blockName,LocCtr);

                            // load the new blockName
                            blockName = "DEFAULT";
                            LocCtr = blockTABLE.getLength(blockName);
                            currentLine = blockTABLE.getLength(blockName);
                            blockCounter = blockTABLE.getBlockNumber(blockName);
                            currentLoc[counter].second = blockTABLE.getLength(blockName);
                            pcLoc[counter+1].second = blockTABLE.getLength(blockName);

                            //blockTABLE.setLength(blockName,LocCtr);

                        } else if(Operand != "")
                        {
                            // Check If there is block exist
                            if(blockTABLE.checkTableExist(Operand))
                            {
                                // if exist change into that table
                                
                                // save previous block to length
                                blockTABLE.setLength(blockName,LocCtr);
                                
                                // change to new block name
                                blockName = Operand;
                                currentLine = blockTABLE.getLength(blockName);
                                blockCounter = blockTABLE.getBlockNumber(blockName);
                                currentLoc[counter].second = blockTABLE.getLength(blockName);
                                pcLoc[counter+1].second = blockTABLE.getLength(blockName);

                                LocCtr = blockTABLE.getLength(blockName);
                                //blockTABLE.setLength(blockName,LocCtr);
                            }
                            else    // else add new block
                            {
                                // New block start at zero
                                //std::cout << "CHANGING TO BLOCK:" << Operand << std::endl;

                                // save previous blockname
                                blockTABLE.setLength(blockName,LocCtr);

                                // add new block to blockTable
                                blockCounter++;
                                blockName = Operand;
                                blockTABLE.bTable.address = 0;
                                blockTABLE.bTable.length = 0;
                                blockTABLE.bTable.blockNumber = blockCounter;

                                // start at locCtr 0
                                LocCtr = 0;
                                currentLoc[counter].second = 0;
                                pcLoc[counter+1].second = 0;
                                blockTABLE.insertTable(Operand,blockTABLE.bTable);
                            }
                        }

                        //std::cout << "CHANGING TO BLOCK:" << Operand << std::endl;
                        //blockTABLE.debug();

                    }

                    // if not comment line
                    if(Label[0] != '.')
                    {
                        currentLoc.push_back({counter,LocCtr});
                        // if there is symbol in label field
                        if(Label != "")
                        {

                            if(symTable.checkTableExist(Label))
                            {
                                std::cout << LocCtr << ": " << Label << std::endl;

                                symTable.setBlockNumber(Label,blockCounter);
                                //std::cout << "testing: Duplicated Symbol Found";
                                //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                                symbolF = true;

                            }else
                            {   
                                //std::cout << "inserted in " ;
                                //std::cout  << "[" << Label << "] [" << LocCtr << "]" << std::endl;
                                symTable.quickInsert(Label,LocCtr);
                                symTable.setBlockNumber(Label,blockCounter);

                                
                            }
                        }// end if symbol


                        if(Operand[0] == '=')
                        {
                            literalTable.resetTable();
                            //std::cout << "LITERAL: " << std::endl;


                            std::istringstream iss(Operand);
                            std::string temp;
                            std::string result;
                            std::string type;

                            int byte;
                            while(std::getline(iss,temp,'\''))
                            {
                                if(temp != "=C" || temp != "X" || temp != "=X")
                                {
                                    result = temp;
                                }
                                if(temp == "=C" || temp == "X" || temp == "=X")
                                {
                                    type = temp;
                                }
                            }
                            //std::cout << "TEMP: " << result << std::endl;
                            //std::cout << "type: " << type << std::endl;
                            
                            int length;
                            std::strtol(result.c_str(),nullptr,16);
                            byte = (result.length() +1)/2;

                            if(type == "=C")
                            {
                                //std::cout << "ResultC" << result << std::endl;
                                length = result.size();
                                result = converter.byteCalc(result);
                            }
                            else if (type == "X")
                            {
                                //std::cout << "ResultX" << result << std::endl;
                                result = result;
                                
                            }
                            else if (type == "=X")
                            {
                                //std::cout << "Result=X" << result << std::endl;
                                length = byte;
                                result = result;
                            }

                            //std::cout << "result: " << result << std::endl;
                            //std::cout << "byyte: " << byte << std::endl;

                            
                            if(literalTable.checkTableExist(Operand))
                            {
                                // skip it exist already 
                            }
                            else
                            {
                                //std::cout << "NEW INSERT: " << Operand << std::endl;
                                literalTable.literalTable.length = converter.intToString(length);
                                literalTable.literalTable.operand = result;
                                literalTable.insertTable(Operand,literalTable.literalTable);
                                //std::cout << "Insert End: " << Operand << std::endl;

                            }
                        }


                        //Search OPTAB for code
                        //temp 
                        std::string eCode = OpCode;
                        eCode.erase(0,1);

                        // Check If Optable exist
                        if(OPTABLE.checkOpExist(OpCode))
                        {
                            //std::cout << "OpCODE: " << OpCode << std::endl;
                            int format = OPTABLE.getFormat(OpCode);
                            if(format == 3)
                            {
                                LocCtr += 3;
                            }
                            else if (format = 2)
                            {
                                LocCtr += 2;
                            }else if (format = 1){

                                LocCtr += 1;
                            }
                        }
                        else if(OpCode == "WORD")
                        {
                            LocCtr += 3;
                        }
                        else if (OpCode == "RESW")
                        {
                            int temp = converter.stringToInt(Operand);
                            LocCtr += (3*temp);
                        }
                        else if (OpCode == "RESB")
                        {
                            // add #operand 
                            // remember its binary need to switch to hex later
                            LocCtr += converter.stringToInt(Operand);  
                        }
                        else if (OpCode == "BYTE")
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
                            //std::cout << "HERE TYEP: " << type << std::endl;
                            //std::cout << "HERE result: " << result << std::endl;
                            //std::cout << "result rseult: " << (256/converter.hexToBinary(result)) << std::endl;

                            // convert result to hex, then calculate byte
                            std::strtol(result.c_str(),nullptr,16);
                            byte = (result.length() +1)/2;

                            //std::cout << "BYTE: " << byte << std::endl;
                            if(type == "C")
                            {
                                LocCtr += result.size();
                            }
                            else if (type == "X")
                            {
                                //LocCtr += (256%converter.hexToBinary(result))/256 + 1;   
                                LocCtr += byte;

                            }
                            else if (type == "=X")
                            {
                                //LocCtr += (256%converter.hexToBinary(result))/256 + 1;   
                                LocCtr += result.size();

                            }

                            // find length of constant in byte
                            // add length to locctr

                        }else if (OPTABLE.checkOpExist(eCode))
                        {
                            //std::cout << OpCode << std::endl;

                            if(OpCode[0] == '+'){

                                LocCtr += 4; 
                            }
                        }
                        else if(OpCode == "LTORG")
                        {
                            //literalTable.debug();

                            fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
                            fReader.newLine();
                            
                            if(literalTable.libTable.empty())
                            {

                            }
                            else
                            {
                                for (auto& it : literalTable.libTable) 
                                {
                                    std::string literal = it.first;
                                    std::string operandName = it.second.operand;
                                    std::string bytes = it.second.length;
                                    it.second.address = converter.intToString(LocCtr);

                                    LocCtr += converter.stringToInt(bytes);


                                    fReader.writeToFile(converter.intToString(LocCtr),"*",literal);
                                    fReader.writeToFile("/t");

                                    fReader.writeToFile(converter.intToString(blockCounter));

                                    if(symTable.checkTableExist(literal))
                                    {

                                    }
                                    else
                                    {
                                        symTable.quickInsert(literal,0,blockCounter);
                                    }


                                    fReader.newLine();
                                    literalDupe.push_back(literal);
                                }
                            }

                        }
                        else if(OpCode == "EQU")
                        {
                            if(symTable.checkTableExist(Label))
                            {
                                if(Operand == "*")
                                {
                                    symTable.setAddress(Label, LocCtr);
                                }
                                else
                                {
                                
                                    std::istringstream iss(Operand);
                                    std::string temp;
                                    std::string result1;
                                    std::string result2;
            
                                    std::string mathType;
                                    int byte;

                                    bool keepGoing = true;

                                    //std::cout << "OPERNAD CHECK: " << Operand << std::endl;

                                    for(int i = 0; i < Operand.size(); i++)
                                    {

                                        if(Operand[i] == '+' || Operand[i] == '-' || Operand[i] == '*' || Operand[i] == '/')
                                        {
                                            mathType = Operand[i];
                                            keepGoing = false;
                                        }
                                        else if(keepGoing)
                                        {
                                            result1 += Operand[i];
                                        }
                                        else
                                        {
                                            result2 += Operand[i];
                                        }

                                        //std::cout << "CURRENT: " << Operand[i] << std::endl;

                                    }
                                    int first, second, final;

                                    //std::cout << "MATHRESULT: [" << result1 << "][" <<  mathType << "][" << result2 << "]." << std::endl;

                                    if(symTable.checkTableExist(result1))
                                    {
                                        
                                        first = symTable.getAddress(result1);
                                    }
                                    else
                                    {
                                        
                                        first = converter.stringToInt(result1);
                                    }

                                    if(symTable.checkTableExist(result2))
                                    {
                                        
                                        second = symTable.getAddress(result2);
                                    }
                                    else
                                    {
                                        second = converter.stringToInt(result2);
                                    }

                                    if(mathType == "-")
                                    {
                                        final = first - second;
                                    } else if (mathType == "+")
                                    {
                                        final = first + second;
                                    }else if (mathType == "/")
                                    {
                                        final = first / second;           
                                    }else if (mathType == "*")
                                    {
                                        final = first * second;
                                    }

                                    std::cout << "FINAL: " << final << std::endl;

                                    symTable.setAddress(Label,final);
                                    LocCtr = final;

                                }   // end whilke

                            

                            }

                            //std::cout << "OPERAND: " << Operand << " opcode: " << OpCode << std::endl;
                        }
                        else
                        {
                            
                            //std::cout << "Error Flag invalid Operation Code";

                            if(OpCode == "BASE")
                            {

                                //std::cout << " I SHOULD INSERT  " << std::endl;
                                symTable.quickInsert(OpCode,LocCtr);


                            }
                            errorF = true;
                            //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                        }   // end check optab for opcode

                        errorFlag.push_back(errorF);
                        symbolFlag.push_back(symbolF);

                        if (OpCode == "LTORG")
                        {
                            readNextInput();
                        }
                        else if(OpCode == "EQU")
                        {
                            fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
                            //fReader.writeToFile(converter.intToString(errorF));
                            //fReader.writeToFile(converter.intToString(symbolF));

                            //fReader.writeToFile("BNUM" + converter.intToString(blockCounter));
                            
                            fReader.newLine();
                            int temp = counter - 1;
                            LocCtr = pcLoc[temp].second;
                            readNextInput();
                        }
                        else
                        {
                            fReader.writeToFile(converter.intToString(currentLoc[counter].second),Label,OpCode,Operand);
                            //fReader.writeToFile(converter.intToString(errorF));
                            //fReader.writeToFile(converter.intToString(symbolF));
                            fReader.writeToFile(converter.intToString(blockCounter));

                            fReader.newLine();
                            readNextInput();
                        }

                        pcLoc.push_back({counter,LocCtr});
                        counter++;

                    }
                    else
                    {
                        readNextInput();
                    } // end if not comment



                    if(Label[0] == '.')
                    {

                    }else
                    {
                        //std::cout << "wrote Line: " << std::endl;
                        //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;

                    }
                    // write to line intermediate
                    // read next input line 


                } // end while not end

            //std::cout << "Testing Input Place Here2!" << std::endl;

            // write last line to intermediate file
            errorFlag.push_back(errorF);
            symbolFlag.push_back(symbolF);
            fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
            //fReader.writeToFile(converter.intToString(errorF));
            //fReader.writeToFile(converter.intToString(symbolF));
            fReader.writeToFile(converter.intToString(blockCounter));

            fReader.newLine();


            blockTABLE.setLength(blockName,LocCtr);
            programLength = LocCtr - startAdd;

            // update block table
            bool first = true;
            for(auto it = blockTABLE.blockTable.rbegin(); it != blockTABLE.blockTable.rend(); it++)
            {
                int length; 
                int address; 
                int value;   
                if(first)
                {
                    if(it->first != "DEFAULT")
                    {
                        blockTABLE.setAddress(it->first,value);
                    }
                    length = it->second.length;
                    address = it->second.address;
                    value = length + address;
                    first = false;
                }
                else
                {
                    blockTABLE.setAddress(it->first,value);
                    length = it->second.length;
                    address = it->second.address;
                    value = length + address;
                    first = true;
                }
            }

            // check lietral 
            for (auto& it : literalTable.libTable) 
            {
                std::string literal = it.first;
                std::string operandName = it.second.operand;
                std::string address = it.second.address;
                std::string bytes = it.second.length;

                if (std::find(literalDupe.begin(), literalDupe.end(),literal)!=literalDupe.end())
                {
        
                }
                else
                {
                    //symTable.quickInsert


                    it.second.address = converter.intToString(LocCtr);
                    fReader.writeToFile(converter.intToString(LocCtr),"*",literal);
                    fReader.writeToFile("\t");
                    fReader.newLine();
                    literalDupe.push_back(literal);
                }
            }
            //std::cout << "block debug: " << std::endl;


            //debug();
            std::cout << "Program Length: " << programLength << std::endl;
            fReader.closeReadFile();
            fReader.closeWriteFile();

    } // end if


} // end pass1 function

void Pass1::readNextInput()
{
    std::getline(fReader.myFile,currentLine);
    ss.clear();
    ss.str(std::string());
    ss << currentLine;
    std::getline(ss, Label, '\t');
    std::getline(ss, OpCode, '\t');
    std::getline(ss, Operand, '\t');
    std::getline(ss, Comment, '\t');

    errorF = false;
    symbolF = false;

}


void Pass1::debug()
{

    //for(int i = 0; i < OpCodeList.size(); i++)
    //{
    //    std::cout  << "[" << LabelList.at(i) << "] [" << OpCodeList.at(i) << "] [" << OperandList.at(i) << "] " << std::endl;
    //}

    int countLine = 0;
    for (const auto& element : currentLoc) {
        countLine += 5;
        std::cout << "(" << countLine;
        std::cout << "). " << element.first << ": " << converter.binaryToHex(element.second) << std::endl;
    }
    for (const auto& element : pcLoc) {
        std::cout << "Element at index " << element.first << ": " << converter.binaryToHex(element.second) << std::endl;
    }

}

