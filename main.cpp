// main.cpp

#include <iostream>
#include <map>

#include "src/header/Optable.h"
#include <fstream>

#include "src/header/Symtable.h"
#include "math/conversion.h"
#include "src/header/Pass1.h"
#include "src/header/FileReader.h"

#include <vector>

std::map<std::string, std::pair<int, std::string>> OPTABLE;

void createOPTABLE()
{
    OPTABLE["Test"] = std::make_pair(3, "18");

}



int main()
{

    std::string test = "Test";
    Optable op;
    //op.createTable();

    //op.debug();
    //std::cout << "if it exist: " << op.checkOpExist("ADDfR") << std::endl;
    std::vector<int> index;
    std::vector<std::string> labelList;
    std::vector<std::string> OpCodeList;
    std::vector<std::string> OperandList;
    std::vector<std::string> SymbolList;
    std::vector<std::string> CommentList;




    Conversion cc;

    std::string sTest = cc.intToString(12345);
    int iTest = cc.stringToInt("99");

    //std::cout << iTest << " : " << sTest << std::endl;



    //Symtable sym;
    //sym.insertTable("mom",1);
    //sym.insertTable("1234",1);
    //sym.insertTable("MOM",13213);
    //sym.insertTable("START",0000);
    //sym.insertTable("BEGIN",13);
    //sym.insertTable("666",1);
    //sym.debug();
    //std::cout << "table exist: " << sym.checkTableExist("BEGIN") << std::endl;
    //std::cout << "get ADDRESS " << sym.getAddress("BEGIN") << std::endl;

/*
    Conversion c;

    c.convertBinToHex(44);

    c.convertBinToHex(15);
    c.convertBinToHex(15);
    c.convertBinToHex(15);

    std::cout << "BinaryToHexTest: " << c.binaryToHex(15) << std::endl;
    std::cout << "HextoBinary: " << c.hexToBinary("15") << std::endl;

    */

    Conversion c;


    std::ifstream myFile;
    std::string currentLine;

    FileReader fr;


    Pass1 p1;

    p1.setFileName("basic");
    p1.beginPass1();
    p1.symTable.debug();



    std::string firstFile = "Immediate/";
    std::string endFile = ".txt";
    std::string fName = "basicTest";
    std::stringstream sss;

    std::cout << c.binaryToHexByte(0) << std::endl;

    std::cout << "STL: " << c.decimalToHexFour(5);

    std::cout << c.decimalToHexTwo(4) << std::endl;


    //bool n,i,x,b,p,e = true;


    //std::cout << "N: " << e << std::endl;

/*
    sss << firstFile << fName << endFile;

    std::cout << sss.str() << std::endl;
    
    
    fr.writeFile(sss.str());


    fr.writeToFile("Test1");
    fr.writeToFile("Test2");
    fr.writeToFile("Test3");
    fr.writeToFile("Test4");
    fr.newLine();
    fr.writeToFile("Test1","test2","test3");
    fr.newLine();
    fr.writeToFile("Test1","test2","test3");

    fr.writeToFile("Test1");

    
    fr.closeWriteFile();

    */

    /*
    std::ofstream outFile;

    outFile.open(sss.str());

    outFile << "test1\ttest2\ttest3\ttest4\n";
    outFile << "test1\t" << "test2\t" << "test3\t" << "test4\n";
    outFile << "test1\t" << "test2\t" << "test3\t" << "test4\n";
    outFile << "test1\t" << "test2\t" << "test3\t" << "test4\n";

    outFile.close();

   
    myFile.open(sss.str());

    if(myFile.fail())
    {
 		std::cout << "Error opening the file : "  << std::endl;
		exit(1);
    }

    */

   /*

    std::string r;

    myFile.open("Input/basicStart.txt");

    int lineIndex = 0;
    if (myFile.is_open()) {
        while (std::getline(myFile,currentLine)) {  
            std::getline(myFile,currentLine);
            // use ss to get the current line
            std::stringstream ss;
            ss << currentLine;

            std::string Symbol, OpCode, Operand, Comment;
            // get Symbol, OpCode, Operand split by tab
            std::getline(ss, Symbol, '\t');
            std::getline(ss, OpCode, '\t');
            std::getline(ss, Operand, '\t');


            //hex std::setfill('0') << std::setw(4)
            // ignore comment 
            std::getline(ss, Comment, '\t');

            //index.push_back(lineIndex);

            // ignore comment line 
            if(Symbol[0] == '.')
            {
                std::cout << "testing: " << Symbol << std::endl;

            }else
            {
                SymbolList.push_back(Symbol);
                OpCodeList.push_back(OpCode);
                OperandList.push_back(Operand);
            }
            

            //Comm.push_back(lineIndex);
            std::cout << lineIndex <<"): T1: [" << Symbol << "] T2: [" << OpCode << "] T3: [" << Operand << "] T4: [" << Comment << "]" <<std::endl;
            lineIndex++;
        }
    }
    myFile.close();

    */

   /*
    std::cout << "testing values: " << OpCodeList[4] << std::endl;

    // list 
    for(int i = 0; i < OpCodeList.size(); i++)
    {
        std::cout  << "[" << SymbolList.at(i) << "] [" << OpCodeList.at(i) << "] [" << OperandList.at(i) << "] " << std::endl;
    }


    */



    std::cout << "end test" << std::endl;



    //std::cout << OPTABLE[test].first << " " << OPTABLE[test].second << std::endl;








}