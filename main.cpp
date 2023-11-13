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

#include <vector>

std::map<std::string, std::pair<int, std::string>> OPTABLE;

void createOPTABLE()
{
    OPTABLE["Test"] = std::make_pair(3, "18");

}



int main()
{




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

    p1.setFileName("functions");
    p1.beginPass1();
    p1.symTable.debug();


    Pass2 p2;

    p2.setFileName("functions");
    p2.setOptable(p1.OPTABLE);
    p2.setSymtable(p1.symTable);
    p2.getPassData(p1.startAdd,p1.LocCtr,p1.programLength);
    p2.beginPass2();


    //std::cout << "CHECKBASEEXIST: " << p2.symTable.checkTableExist("BASE") << std::endl;



    std::string firstFile = "Immediate/";
    std::string endFile = ".txt";
    std::string fName = "basicTest";
    std::stringstream sss;

    std::cout << c.binaryToHexByte(0) << std::endl;

    std::cout << "STL: " << c.decimalToHexFour(5);

    std::cout << c.decimalToHexTwo(4) << std::endl;


    /*
    std::string parse = "=X'EOF'";
    
    std::stringstream parser;
    std::istringstream parsing(parse);
    std::string temp;

    std::string emoji;

    std::string type;;

    while(std::getline(parsing, temp, '\'')) {
        if(temp != "C" || temp != "X" || temp != "=X")
        {
            emoji = temp;
        }
         if(temp != "C" || temp != "X" || temp != "=X")
         {
            std::cout << temp << ", " << std::endl;
            type = temp;
        }
    }
    */




    //std::cout << "type [" << type << ("]EmoJI: ")  << emoji.size() << std::endl;



    std::cout << "testing for op counter__ " << std::endl; 

    // get format/code

    std::string opcode = "0C";

    // check format 

    // get printable
    std::string opcode6 = c.decimalToHexTwo(opcode);
    std::cout << "hex2 : " << opcode6 << std::endl;


/*
    // set bits
    std::string n,i,x,b,p,e;

    n = "1";
    i = "1";
    x = "0";
    b = "0";
    p = "1";
    e = "0";

    // check for pc/b

    // pc is next instruction
    std::string pc = "26";
    std::string length = "33";
    int disp = c.hexToBinary(length) - c.hexToBinary(pc);

    // displacement 
    //std::string opcode6 = c.binaryToHex(disp);
    //std::cout << "opcode6 == " << opcode6 << std::endl;

    std::string displacement = c.displacement(disp);
    std::cout << "final disp " << displacement << std::endl;

    std::cout << "hex4 : " << c.decimalToHexFour(opcode)<< std::endl;

    std::stringstream operand1;

    operand1 << opcode6 << n << i << x << b << p << e << displacement;

    std::string fresult = operand1.str();
    
    std::cout << "RESUTL : " << fresult << std::endl;

    std::cout << "OPCODE: " << c.opcodeHex(fresult) << std::endl;


*/


    // test format 2 
    // Clear X 

    // B4  +  A + B

    std::string lda = "+lda";


    std::stringstream ppp;
    std::istringstream testing123(lda);
    std::string temp1;

    std::string extended;
    std::string indirection;

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

    std::cout << OpCode.size() << std::endl;


    if(format == 3)
    {
        n = 1, i = 1;
    } 

    // check OpCode
    while(keepGoing)
    {
        // extended
        if(OpCode.at(ij) == '+')
        {
            e = 1;
        }

        ij++;
        if(ij >= OpCode.size())
        {
            keepGoing = false;      
        }
    }

    if(Operand == "")
    {
        x = 0;
        b = 0;
        p = 0;
        e = 0;
    }
    else
    {
        keepGoing = true;
        ij = 0;
        while(keepGoing)
        {
            // immediate
            if(Operand.at(ij) == '#')
            {
                i = 1; n = 0;
            }
            // addressing
            if(Operand.at(ij) == '@')
            {
                i = 0; n = 1;
            }

            if(Operand.at(ij) == ',')
            {
                x = 1;
                keepGoing = false;
            }

            ij++;
            if(ij >= Operand.size())
            {
                keepGoing = false;
                std::cout << "i2 : " << ij << std::endl;            
            }
        }
    }


    // check pc 
    if(Operand != "")
    {
        b = 0; p = 1;

    }
    else
    {

    }


    // self check extend immediate 
    // b = 0; p = 0;

    std::stringstream operand1;


    //int displacement = c.displacement(c.calculateDisplacement(step12));


    // displacement = Address of target - pc/b
    // using Hex input string to int 
    int disp = lenAddr - pcAddr;
    
    // immediate extend
    std::string disp2 = c.displacementExtend(lenAddr);
    std::string displacement;
    //int disp = 0;




    GenerateOp genOp;

    int tester123 = -2048;

    //std::cout << "CHECK DISPLACEMENT: " << genOp.checkPC(tester123) << std::endl;

    if(e)
    {
        displacement = c.displacementExtend(disp);
    }else
    {
        displacement = c.displacement(disp);
        std::cout << "TEST" << std::endl;
    }

  
    std::cout << "displacement: " << displacement << std::endl;


    // convert Opcode into either 0000 00 or 0000 0000 depending 
    std::string opcode61 = c.decimalToHexTwo(OpCodeT);        
    // create the bits into stringstream
    operand1 << opcode61 << n << i << x << b << p << e << displacement;  
    
    // use opcode hex to convert into hex if not immediate
    std::string firstHalf = c.opcodeHex(operand1.str());

    // if immedidate etc

    std::cout << "Firsthalf : " << firstHalf << std::endl;


    std::cout << "Second Half: " << disp2 << std::endl;


    std::cout << "OperandString: " << operand1.str() << std::endl;

    std::cout << "obama: " <<  c.opcodeHex(operand1.str())<< std::endl;


    int step12 = lenAddr - pcAddr;


    // 4062
    //int pcAddr = 16482; 
    // 4036
    //int lenAddr = 16438;

    std::string pc = c.intToString(pcAddr);
    std::string length = c.intToString(lenAddr);



    //std::cout << "test: " << c.binaryToHex(disp) << std::endl;

    //std::cout << "test1: " << c.displacement(disp) << std::endl;


    //std::cout << "hex to binary: " <<c.hexToBinary(pcAddr)  << std::endl;


    //std::cout << "DISP: " << disp << std::endl;  


    std::cout << "NIXBPE" << std::endl;
    std::cout << n << i << x << b << p << e << std::endl;


    //std::cout << c.decimalToHexFour) << std::endl;

    /*
    
    std::cout << "htob: " << c.hexToBinary("FF") << std::endl;

    int amount = c.hexToBinary("105");

    std::string tester = "F1";

    int hexInt = std::strtol(tester.c_str(), nullptr, 16);

    std::cout << "hexInt:" << hexInt << std::endl;

    std::cout << "AMOUNT : " << amount << std::endl;

    int counter = (tester.length() + 1)/2;

    std::cout << "COUTNER LOGIC: " << counter << std::endl;



    int t1 = 256-241;

    std::cout << "result: " << (amount% 256) / 256 + 1 << std::endl;


    */


    //bool n,i,x,b,p,e = true;


    //std::cout << "N: " << e << std::endl;


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