// __Pass1.cpp__

#include "../header/Pass1.h"

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

void Pass1::beginPass1()
{

    // LOCCTR, Label, Opcode, Operand || ignore comment line
    fReader.writeFile("Immediate/" + fileName + "testIMT.txt");

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

                //std::cout << "new Line: " << std::endl;
                //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;

            while(OpCode != "END")
                {
                    std::cout  << "[Loc:" << LocCtr << "] [Label:" << Label << "] [OPcode:" << OpCode << "] [Operand:" << Operand << "]" << std::endl;


                    fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
                    fReader.newLine();
                    //std::cout  << "[Loc:" << LocCtr << "] [Label:" << Label << "] [OPcode:" << OpCode << "] [Operand:" << Operand << "]" << std::endl;

                    // if not comment line
                    if(Label[0] != '.')
                    {
                        // if there is symbol in label field
                        if(Label != "")
                        {
                            if(symTable.checkTableExist(Label))
                            {
                                //std::cout << "testing: Duplicated Symbol Found" << std::endl;
                            }else
                            {   
                                //std::cout << "inserted in " ;
                                //std::cout  << "[" << Label << "] [" << LocCtr << "]" << std::endl;
                                symTable.insertTable(Label,LocCtr);
                            }

                        }// end if symbol

                        //Search OPTAB for code

                        if(OPTABLE.checkOpExist(OpCode))
                        {
                            //std::cout << "OpCODE: " << OpCode << std::endl;
                            LocCtr += 3;
                        }
                        else if(OpCode == "WORD")
                        {
                            LocCtr += 3;
                        }
                        else if (OpCode == "RESW")
                        {
                            int temp = converter.stringToInt(Operand);
                            LocCtr += (3*temp);
                            //std::cout << "Label: " << Label << std::endl;
                        }
                        else if (OpCode == "RESB")
                        {
                            // add #operand 
                            // remember its binary need to switch to hex later
                            LocCtr += converter.stringToInt(Operand);  
                        }
                        else if (OpCode == "BYTE")
                        {
                            // find length of constant in byte
                            // add length to locctr

                        }
                        else
                        {
                            std::cout << "Error Flag invalid Operation Code" << std::endl;
                            std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                        }   // end check optab for opcode

                    }
                    else
                    {
                        // if there is a comment 
                        //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                    } // end if not comment

                    if(Label[0] == '.')
                    {
                        readNextInput();
                    }else
                    {
                        //std::cout << "wrote Line: " << std::endl;
                        //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;
                        
                        //std::cout  << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;


                        readNextInput();

        
                    }
                    // write to line intermediate

                    // read next input line 


                } // end while not end

            //std::cout << "Testing Input Place Here2!" << std::endl;

            // write last line to intermediate file
            fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
            fReader.newLine();
            
            programLength = LocCtr - startAdd;

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
}


void Pass1::debug()
{

    for(int i = 0; i < OpCodeList.size(); i++)
    {
        std::cout  << "[" << LabelList.at(i) << "] [" << OpCodeList.at(i) << "] [" << OperandList.at(i) << "] " << std::endl;
    }
}

