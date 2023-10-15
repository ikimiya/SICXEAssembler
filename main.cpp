// main.cpp

#include <iostream>
#include <map>

//#include "Optable.h"
#include <fstream>

#include "src/header/Symtable.h"
#include "math/conversion.h"

std::map<std::string, std::pair<int, std::string>> OPTABLE;

void createOPTABLE()
{
    OPTABLE["Test"] = std::make_pair(3, "18");

}



int main()
{

    std::string test = "Test";
    //Optable op;
    //op.createTable();
    //op.debug();


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

    Conversion c;

    c.convertBinToHex(44);

    c.convertBinToHex(15);
    c.convertBinToHex(15);
    c.convertBinToHex(15);

    std::cout << "BinaryToHexTest: " << c.binaryToHex(15) << std::endl;
    std::cout << "HextoBinary: " << c.hexToBinary("15") << std::endl;



    std::ifstream myFile;
    std::string currentLine;

    myFile.open("Input/functions.txt");

    if(myFile.fail())
    {
 		std::cout << "Error opening the file : "  << std::endl;
		exit(1);
    }

    std::string x,y,z,r;


    /*
    if (myFile.is_open()) {
        while (myFile) {
            // Print the data of the string.     
            myFile >> x >> y >> z;

            std::cout << "1: [" << x << "] 2: [" << y << "] 3: [" << z << "]" << "4: [" << r << "]"
            <<std::endl;
        }
    }
    */



    myFile.close();




    std::cout << "end test" << std::endl;



    //std::cout << OPTABLE[test].first << " " << OPTABLE[test].second << std::endl;








}