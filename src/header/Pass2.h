// __Pass2.h__

#ifndef __PASS2_H__
#define __PASS2_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "../header/Symtable.h"
#include "../header/Libtab.h"

#include "../header/FileReader.h"
#include "../../Math/Conversion.h"
#include "../header/Optable.h"
#include "../header/GenerateOp.h"
#include "../header/OpcodeStruct.h"
#include "../header/blockTable.h"

class Pass2
{   
    
    public:
        
        Pass2();
        ~Pass2();

        void setFileName(std::string fileName);

        void beginPass2();

        void readNextInput();

        void setOptable(Optable op);
        void setSymtable(Symtable sym);
        void setLiteralTab(Libtab lit);
        void setBlockTab(BlockTable bloc);

        void setLocation(std::vector<std::pair<int,int>> curLoc, std::vector<std::pair<int,int>> nextLoc);

        void writeHeader();

        Optable getOptable(Optable op);
        Symtable getSymtable(Symtable sym);



        void getPassData(int starting, int loc, int pLength);

        void debug();



        Symtable symTable;
        Optable OPTABLE;

        FileReader fReader;
        Conversion converter;
        GenerateOp genOp;
        Libtab literalTable;
        BlockTable blockTABLE;
    

        std::string fileName;

        std::string currentLine; 
        std::string Address, Label, OpCode, Operand;
        std::string blockNumber;

        std::stringstream ss;
        
        int startAdd;
        int LocCtr;
        int programLength;

        std::vector<std::pair<int,int>> currentLoc;
        std::vector<std::pair<int,int>> pcLoc;
        int counter = 0;


        std::string symbolAddress;


        OpcodeStruct opStruct;

};


#endif // 