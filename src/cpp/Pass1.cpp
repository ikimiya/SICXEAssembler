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
                fReader.writeToFile(converter.intToString(errorF));
                fReader.writeToFile(converter.intToString(symbolF));
                fReader.newLine();

                // read next line 
                //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
/*
                std::getline(fReader.myFile,currentLine);
                ss.clear();
                ss.str(std::string());
                ss << currentLine;
                std::getline(ss, Label, '\t');
                std::getline(ss, OpCode, '\t');
                std::getline(ss, Operand, '\t');
                std::getline(ss, Comment, '\t');

                */
                readNextInput();
                
            }// end if start
            else{
                LocCtr = 0;
            }   

            while(OpCode != "END")
                {
                    // if not comment line
                    if(Label[0] != '.')
                    {
                        // if there is symbol in label field
                        if(Label != "")
                        {
                            if(symTable.checkTableExist(Label))
                            {
                                std::cout << LocCtr << ": " << Label << std::endl;
                                //std::cout << "testing: Duplicated Symbol Found";
                                //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                                symbolF = true;

                            }else
                            {   
                                //std::cout << "inserted in " ;
                                //std::cout  << "[" << Label << "] [" << LocCtr << "]" << std::endl;
                                symTable.insertTable(Label,LocCtr);
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
                                std::cout << "NEW INSERT: " << Operand << std::endl;
                                literalTable.literalTable.length = converter.intToString(length);
                                literalTable.literalTable.operand = result;
                                //std::cout << "result: " << length << std::endl;
                                literalTable.insertTable(Operand,literalTable.literalTable);
                                std::cout << "Insert End: " << Operand << std::endl;

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
                            std::cout << "OH MY LORD scan" << std::endl;
                            literalTable.debug();

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
                                    //std::string address = it.second.address;
                                    std::string bytes = it.second.length;
                                    it.second.address = converter.intToString(LocCtr);
                                    
                                    LocCtr += converter.stringToInt(bytes);


                                    fReader.writeToFile(converter.intToString(LocCtr),"*",literal);
                                    fReader.writeToFile("");
                                    fReader.writeToFile(operandName);

                                    fReader.newLine();
                                    literalDupe.push_back(literal);
                                }
                            }

                        }
                        else
                        {
                            
                            //std::cout << "Error Flag invalid Operation Code";

                            if(OpCode == "BASE")
                            {

                                //std::cout << " I SHOULD INSERT  " << std::endl;
                                symTable.insertTable(OpCode,LocCtr);


                            }
                            errorF = true;
                            //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                        }   // end check optab for opcode

                        errorFlag.push_back(errorF);
                        symbolFlag.push_back(symbolF);

                    if (OpCode == "LTORG")
                    {
                        readNextInput();
                    }else
                    {
                        fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
                        fReader.writeToFile(converter.intToString(errorF));
                        fReader.writeToFile(converter.intToString(symbolF));
                        fReader.newLine();
                        readNextInput();
                    }
                    

                    }
                    else
                    {
                        // if there is a comment 
                        //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                        readNextInput();

                    } // end if not comment



                    if(Label[0] == '.')
                    {
                        //std::cout  << ". ): [Loc:" << LocCtr << "] [Label:" << Label << "] [OPcode:" << OpCode << "] [Operand:" << Operand << "]" << std::endl;

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
            fReader.writeToFile(converter.intToString(errorF));
            fReader.writeToFile(converter.intToString(symbolF));

            fReader.newLine();
            
            programLength = LocCtr - startAdd;



            // check again 

            for (auto& it : literalTable.libTable) 
            {
                std::string literal = it.first;
                std::string operandName = it.second.operand;
                std::string address = it.second.address;
                std::string bytes = it.second.length;

                std::cout << "operand Name: " << operandName << std::endl;

                if (std::find(literalDupe.begin(), literalDupe.end(),literal)!=literalDupe.end())
                {
                    

                }
                else
                {
                    it.second.address = converter.intToString(LocCtr);

                    fReader.writeToFile(converter.intToString(LocCtr),"*",literal);
                    fReader.writeToFile("\t" + operandName);
                    fReader.newLine();
                    literalDupe.push_back(literal);
                }
            }




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

    for(int i = 0; i < OpCodeList.size(); i++)
    {
        std::cout  << "[" << LabelList.at(i) << "] [" << OpCodeList.at(i) << "] [" << OperandList.at(i) << "] " << std::endl;
    }
}

