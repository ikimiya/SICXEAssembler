// main.cpp

#include <iostream>
#include <map>

#include "src/header/Optable.h"
#include <fstream>

#include "src/header/Symtable.h"

#include "src/header/Pass1.h"
#include "src/header/Pass2.h"
#include "src/header/FileReader.h"
#include "src/header/GenerateOp.h"
#include "src/header/Libtab.h"

#include <filesystem>

#include <vector>

std::map<std::string, std::pair<int, std::string>> OPTABLE;

void createOPTABLE()
{
    OPTABLE["Test"] = std::make_pair(3, "18");
}



int main()
{

    Symtable sym;

    std::string path = "Input";
    std::string resultPath;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::cout << entry.path().stem() << std::endl;
        resultPath = entry.path().stem().u8string();
    }

    std::cout << resultPath << std::endl;

    std::vector<int> location;

    location.push_back(1);
    location.push_back(21);
    location.push_back(31);
    location.push_back(41);
    location.push_back(51);
    location.push_back(61);

    std::cout << location[1] << std::endl;

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

    struct libValue
    {
        std::string operand;
        std::string length;
        std::string address;
    };

    libValue v;
    v.address = "112312";
    v.length =  "3";
    v.operand = "ieorand";

    std::string f = "first";

    Libtab lib;

    lib.literalTable.address = "112312";
    lib.literalTable.length =  "3";
    lib.literalTable.operand = "ieorand";
    lib.insertTable(f,lib.literalTable);

    lib.resetTable();
    lib.literalTable.address = "4";
    lib.literalTable.length =  "1";
    lib.literalTable.operand = "2";

    
    lib.insertTable("mother",lib.literalTable);

    lib.resetTable();

    lib.literalTable.address = "4";
    lib.literalTable.length =  "1";
    lib.literalTable.operand = "2";
    lib.insertTable("mother",lib.literalTable);

    //lib.debug();


    Conversion c;


    std::ifstream myFile;
    std::string currentLine;

    FileReader fr;

    std::string fileName = "prog_blocks";

    Pass1 p1;

    p1.setFileName(fileName);
    p1.beginPass1();
    //p1.literalTable.debug();

    //std::cout << "symtable.debug()" << std::endl;
    p1.symTable.debug();


    Pass2 p2;

    p2.setFileName(fileName);
    p2.setOptable(p1.OPTABLE);
    p2.setSymtable(p1.symTable);
    p2.setLiteralTab(p1.literalTable);
    p2.setBlockTab(p1.blockTABLE);
    p2.getPassData(p1.startAdd,p1.LocCtr,p1.programLength);
    p2.setLocation(p1.currentLoc,p1.pcLoc);
    p2.beginPass2();


    std::string firstFile = "Immediate/";
    std::string endFile = ".txt";
    std::string fName = "basicTest";
    std::stringstream sss;

    std::cout << c.binaryToHexByte(0) << std::endl;

    std::cout << "STL: " << c.decimalToHexFour(5);

    std::cout << c.decimalToHexTwo(4) << std::endl;



    // get format/code
    std::string opcode = "0C";

    // check format 

    // get printable
    std::string opcode6 = c.decimalToHexTwo(opcode);
    std::cout << "hex2 : " << opcode6 << std::endl;



    std::string lda = "+lda";


    std::istringstream testing123(lda);


    bool keepGoing = true;

    int ij = 0;
    bool n,i,x,b,p,e;    

    std::string OpCode = "ADD";

    std::string OpCodeT = "48";
    std::string Operand = "Table,X";

    // using hex to int 
    // then calculate displacement
    int pcAddr = c.hexToBinary("000C"); 
    int lenAddr = c.hexToBinary("001B");


    int format = 3;


    std::cout << "end test" << std::endl;



}