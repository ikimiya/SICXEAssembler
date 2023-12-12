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

            // Setup Default Blokcs 
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
                controlName = OpCode;
                // save #operand as starting address 
                startAdd = converter.stringToInt(Operand);

                // convert locctr to int
                LocCtr = converter.stringToInt(Operand);

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

            // push start line
            currentLoc.push_back({counter,LocCtr});
            pcLoc.push_back({counter,LocCtr});
            counter++;

            expanding = false;

            while(OpCode != "END")
            {

                //std::cout << "Counter: [" << counter << "] " << "PcCounter: " << "[" << LocCtr << "] [" << Label << "] [" << OpCode << "] [" << Operand << "]" << std::endl;


                if(OpCode == "USE")
                {

                    // if empty, it is default block
                    std::cout << "currentBlockName" << blockName << std::endl;
                    if(Operand == "")
                    {                           
                        // this sets the last locctr to block name
                        blockTABLE.setLength(blockName,LocCtr);

                        // load the new blockName
                        blockName = "DEFAULT";
                        LocCtr = blockTABLE.getLength(blockName);
                        currentLine = blockTABLE.getLength(blockName);
                        blockCounter = blockTABLE.getBlockNumber(blockName);
                        currentLoc[counter].second = blockTABLE.getLength(blockName);
                        pcLoc[counter+1].second = blockTABLE.getLength(blockName);

                    }
                    else if(Operand != "")
                    {
                        // Check If there is block exist
                        if(blockTABLE.checkTableExist(Operand))
                        {                                
                            // save previous block to length
                            blockTABLE.setLength(blockName,LocCtr);
                            
                            // change to new block name
                            blockName = Operand;
                            currentLine = blockTABLE.getLength(blockName);
                            blockCounter = blockTABLE.getBlockNumber(blockName);
                            currentLoc[counter].second = blockTABLE.getLength(blockName);
                            pcLoc[counter+1].second = blockTABLE.getLength(blockName);

                            LocCtr = blockTABLE.getLength(blockName);
                        }
                        else    // else add new block
                        {
                            // New block start at zero

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
                    }   // end if program block

                    //std::cout << "CHANGING TO BLOCK:" << Operand << std::endl;
                    //blockTABLE.debug();

                }   // end use 

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
                            if(symTable.getAddress(Label) > LocCtr)
                            {
                                std::string newLabel = Label+controlName;
                                symTable.quickInsert(newLabel,LocCtr);
                            }

                            symbolF = true;

                        }else
                        {   
                            //std::cout << "inserted in " ;
                            

                            if(namTab.checkTableExist(Label))
                            {
                                //std::cout << "checkTTExist: " << Label << std::endl;
                            }
                            else
                            {
                                symTable.quickInsert(Label,LocCtr);
                                symTable.setBlockNumber(Label,blockCounter);

                            }
                              
                        }
                    }// end if symbol

                    // check for literals
                    if(Operand[0] == '=')
                    {
                        literalTable.resetTable();
    
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
                                } 
                                else if (mathType == "+")
                                {
                                    final = first + second;
                                }
                                else if (mathType == "/")
                                {
                                    final = first / second;           
                                }
                                else if (mathType == "*")
                                {
                                    final = first * second;
                                }
                                std::cout << "FINAL: " << final << std::endl;

                                symTable.setAddress(Label,final);
                                
                                LocCtr = final;

                            }   // end equ*

                        }

                        //std::cout << "OPERAND: " << Operand << " opcode: " << OpCode << std::endl;
                    }
                    else if (OpCode == "CSECT")
                    {
                        controlName = Label;
                        LocCtr = 0;
                        currentLoc[counter].second = 0;
                        pcLoc[counter+1].second = 0;
                    }
                        // check if label exist
                    else if(namTab.checkTableExist(OpCode))
                    {
                        //std::cout << "Label Exist Expanding" << std::endl;
                        //std::cout << "Label:" << Label <<" Operand: " << Operand << " OPCODE: " << OpCode << std::endl;

                        // set arg table 
                        std::istringstream iss(Operand);
                        std::string temp;

                        argTab.cleanTable();
                    
                        int argCounter = 0;
                        while(std::getline(iss,temp,','))
                        {
                            //std::cout << "argTable: " << temp << std::endl;
                            argTab.insertTable(temp,argCounter);
                            argCounter++;
                        }

                       

                        //std::cout << "Myarg: " << argTab.getArg(1) << std::endl;

                        // write comment line
                        int beginLine = namTab.getStart(OpCode);
                        int endLine = namTab.getEnd(OpCode);


                        //std::cout << "begin: " << beginLine << " end: " << endLine << std::endl;

                        std::string expandFile = defTab.getMacro(beginLine);
                        
                        std::stringstream ssT;
                        std::stringstream temp2;

                        ssT << expandFile;
                        std::string currentL;

                        std::string fileLoc;
                        std::string Label2;
                        std::string OpCode2;
                        std::string Operand2;

                        std::getline(ssT,currentL);
                        temp2 << currentL;
    
                        std::getline(temp2, fileLoc, '\t');
                        std::getline(temp2, Label2, '\t');
                        std::getline(temp2, OpCode2, '\t');
                        std::getline(temp2, Operand2, '\t');
                        //std::getline(temp2, Comment, '\t');


                        fReader.writeToFile("."+Label,OpCode,Operand);
                        fReader.newLine();

                        bool first = true;
                        beginLine++;

                        while(beginLine != endLine)
                        {
                            bool changeArg = false;
                            std::string expandFile = defTab.getMacro(beginLine);
                            std::stringstream ssT;
                            std::stringstream temp2;

                            ssT << expandFile;
                            std::string currentL;
                            std::string fileLoc;
                            std::string Label2;
                            std::string OpCode2;
                            std::string Operand2;

                            std::getline(ssT,currentL);
                            temp2 << currentL;
        
                            std::getline(temp2, fileLoc, '\t');
                            std::getline(temp2, Label2, '\t');
                            std::getline(temp2, OpCode2, '\t');
                            std::getline(temp2, Operand2, '\t');

                            //std::cout << "Current Operand:[" << Operand2 << "]" << std::endl;
                            std::istringstream iss(Operand2);
                            std::string value1;
                            std::string value2;
                            std::string value3;

                            char currentChar;
                            bool quoteStart = false;
                            bool findQuote = false;
                            
                            while (iss.get(currentChar)) 
                            {
                                if(Operand2[0] == '?')
                                {
                                    quoteStart = true;
                                }

                                if(quoteStart)
                                {
                                    if (currentChar == ',' && !findQuote) {
                                        findQuote = true;
                                        value3 += currentChar;
                                    } 
                                    else if (currentChar == '\'' && findQuote) 
                                    {
                                        value3 += currentChar;
                                    } else {
                                        if (!findQuote) {
                                            value2 += currentChar;
                                        } else {
                                            value3 += currentChar;
                                        }
                                    }
                                }
                                else
                                {
                                    if (currentChar == '\'' && !findQuote) {
                                        findQuote = true;
                                        value1 += currentChar;
                                    } 
                                    else if (currentChar == '\'' && findQuote) 
                                    {
                                        value3 += currentChar;
                                    } else {
                                        if (!findQuote) {
                                            value1 += currentChar;
                                        } else {
                                            value2 += currentChar;
                                        }
                                    }
                                }
                            }   // end while

                            std::string newOperand = Operand2;
                            //std::cout <<  "Value1: [" << value1 << "] " << 
                            //"Value2: [" << value2 << "]" << 
                            //" Value3: [" << value3 << "]" << std::endl;
                        

                            std::string newInt; 
                            int index;
                            if(value2[0] == '?')
                            {
                                int i = 0; 
                                while (i < value2.size()) {
                                    if (value2[i] == '?') 
                                    {
                                        changeArg = true;
                                    } 
                                    else {
                                        newInt += value2[i];
                                    }
                                    i++;
                                }
                                index = converter.stringToInt(newInt);
                                //std::cout << "index test: " << index << std::endl;
                            }
                            
                            if(changeArg)
                            {
                                if(argTab.checkTableExistInt(index))
                                {
                                    newOperand = value1 + argTab.getArg(index) + value3;

                                }
                            
                            }
                        
                            
                            if(first)
                            {
                                Label2 = Label;
                                first = false;
                            }

                            //std::cout << fileLoc << " " << Label2 << " " << OpCode2 << " " << newOperand << std::endl;

                            fReader.writeToFile(fileLoc,Label2,OpCode2,newOperand);
                            fReader.newLine();
                            beginLine++;
                        }
                        
                        readNextInput();
                        //fReader.newLine();

                    }
                
                    else if(OpCode == "MACRO")
                    {
                        // -1, -1 starting
                        std::string macroName = Label;
                        //std::cout << "isMacro:" << macroName << std::endl;
                        namTab.resetTable();
                        int startCounter = defTab.counter;
                        int endCounter;
                        namTab.insertTable(macroName,namTab.namTabLoc);

                        if(namTab.checkTableExist(Label))
                        {
                        }

                        std::istringstream iss(Operand);
                        std::string temp;
                        
                        while(std::getline(iss,temp,','))
                        {
                            //std::cout << "notation: " << temp << std::endl;
                            notation.push_back(temp);
                        }

                        // insert defTable
                        std::stringstream ss;
                        ss << converter.intToString(LocCtr) << "\t" << Label << "\t" << OpCode
                        << "\t" << Operand << "\t" << blockCounter;

                        defTab.insertTable(ss.str());

                        int level = 1;

                        while(level > 0)
                        {
                            readNextInput();
                            bool foundChange = false;

                            if(Label[0] != '.')
                            {

                                std::string value1;
                                std::string value2;
                                std::string value3;

                                //std::cout << "coutner check: " << defTab.counter << std::endl;
                                std::istringstream iss(Operand);
                                //std::string value1;
                                //std::string value2;
                                //std::string value3;
                                char currentChar;

                                bool findQuote = false;
                                bool quoteStart = false;

                                while (iss.get(currentChar)) {

                                    if(Operand[0] == '&')
                                    {
                                        quoteStart = true;
                                    }

                                    if(quoteStart)
                                    {
                                        if (currentChar == ',' && !findQuote) {
                                            findQuote = true;
                                            value3 += currentChar;
                                        } 
                                        else if (currentChar == '\'' && findQuote) 
                                        {
                                            value3 += currentChar;
                                        } else 
                                        {
                                            if (!findQuote) {
                                                value2 += currentChar;
                                            } else {
                                                value3 += currentChar;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (currentChar == '\'' && !findQuote) {
                                            findQuote = true;
                                            value1 += currentChar;
                                        } 
                                        else if (currentChar == '\'' && findQuote) 
                                        {
                                            value3 += currentChar;
                                        } else {

                                            if (!findQuote) {
                                                value1 += currentChar;
                                            } else {
                                                value2 += currentChar;
                                            }
                                        }
                                    }

                                }   // end while find buffer,x etc
                            
                                auto it = std::find(notation.begin(), notation.end(), value2);
                                int index;

                                if (it != notation.end()) {
                                    index = std::distance(notation.begin(), it);
                                    foundChange = true;
                                } else {
                                    //std::cout << "'" << Operand << "' second Not Found" << std::endl;
                                }

                                std::string newOperand = Operand;

                                //std::cout << "Value1: [" << value1 << "]" << std::endl;
                                //std::cout << "Value2: [" << value2 << "]" << std::endl;
                                //std::cout << "Value3: [" << value3 << "]" << std::endl;

                                if(foundChange)
                                {
                                    newOperand = value1 + "?" + converter.intToString(index) + value3;
                                    //std::cout << "NewOperand [" << newOperand << "]" << std::endl;
                                }

                                //if(foundChange)

                                std::stringstream ss;
                                ss << converter.intToString(LocCtr) << "\t" << Label << "\t" << OpCode
                                << "\t" << newOperand << "\t" << blockCounter;

                                //std::cout << ss.str() << std::endl;
                                if(OpCode == "MEND")
                                {

                                }else
                                {
                                    defTab.insertTable(ss.str());
                                }


                                if(OpCode == "MACRO")
                                {
                                    level = level + 1;
                                }
                                else if(OpCode == "MEND")
                                {
                                    level = level - 1;
                                    endCounter = defTab.counter;
                                    
                                }

                            } // end if comment 
                        }   // ene level
                        namTab.setStart(macroName,startCounter);
                        namTab.setEnd(macroName,endCounter);
                        defTab.counter++;

        
                        notation.clear();

                        } // end if macro define
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
                        if(OpCode == "MEND")
                        {
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
                    //fReader.writeToFileTab();
                    LocCtr += converter.stringToInt(it.second.length);
                    fReader.newLine();
                    literalDupe.push_back(literal);
                }
            }

            // write last line to intermediate file
            errorFlag.push_back(errorF);
            symbolFlag.push_back(symbolF);
            fReader.writeToFile(converter.intToString(LocCtr),Label,OpCode,Operand);
            //fReader.writeToFile(converter.intToString(errorF));
            //fReader.writeToFile(converter.intToString(symbolF));
            fReader.writeToFile(converter.intToString(blockCounter));
            fReader.newLine();
            blockTABLE.setLength(blockName,LocCtr);

            pcLoc.push_back({counter,LocCtr});
            currentLoc.push_back({counter,LocCtr});
            counter++;

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




            //std::cout << "block debug: " << std::endl;
            //literalTable.debug();
            //namTab.debug();
            //debug();
            //defTab.debug();
            //blockTABLE.debug();
            programLength = LocCtr - startAdd;
            //std::cout << "highest block: " << blockTABLE.getHighestBlock() << std::endl;

            int highestBlock = blockTABLE.getHighestBlock();

            programLength = blockTABLE.getAddressIndex(highestBlock) + blockTABLE.getLengthIndex(highestBlock);
            


            std::cout << "Program Length: " << programLength << std::endl;
            fReader.closeReadFile();
            fReader.closeWriteFile();

    } // end if


} // end pass1 function

void Pass1::readNextInput()
{
    std::getline(fReader.myFile,currentLine);

    if(currentLine.empty())
    {
        std::cout << "line Empty" << std::endl;
        Label = "";
        OpCode = "";
        Operand = "";
        Comment = "";
        
    }
    else
    {
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

