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
#include "../header/ControlTab.h"


class Pass2
{   
    
    public:
        
        Pass2();
        ~Pass2();

        void setFileName(std::string fileName);

        void beginPass2();

        void readNextInput();

        // set Tables from pass 1
        void setOptable(Optable op);
        void setSymtable(Symtable sym);
        void setLiteralTab(Libtab lit);
        void setBlockTab(BlockTable bloc);
        void setControlTab(ControlTab conT);
        void setLocation(std::vector<std::pair<int,int>> curLoc, std::vector<std::pair<int,int>> nextLoc);
        void debug();

        // return table
        Optable getOptable(Optable op);
        Symtable getSymtable(Symtable sym);
        void getPassData(int starting, int loc, int pLength);

        // writing
        std::stringstream ssObject;
        bool begin = true;
        int textLength = 0;

        void writeHeader();
        void initializeText();
        void writeText();
        void writeObjectCode();

        bool textStarted = false;
        std::stringstream ssMod;
        void initializeMod(std::string word);
        void writeMod();
        void writeEnd();

        Symtable symTable;
        Optable OPTABLE;
        Libtab literalTable;
        BlockTable blockTABLE;
        ControlTab conTab;

        FileReader fReader;
        Conversion converter;
        GenerateOp genOp;
    
        // file Parsing
        std::stringstream ss;

        std::string fileName;
        std::string currentLine; 
        std::string Address, Label, OpCode, Operand;
        std::string blockNumber;

        std::string symbolAddress;
        // address locatiosn        
        int startAdd;
        int LocCtr;
        int programLength;

        std::vector<std::pair<int,int>> currentLoc;
        std::vector<std::pair<int,int>> pcLoc;

        // control section
        std::vector<std::string> externalRef;
        std::vector<std::string> externalDef;
        std::string controlName;
        std::string firstControl;
        bool isCsect = false;

        std::stringstream ssDefine;
        std::stringstream ssRecord;
        void writeDefine();
        void writeRecord();
        int counter = 0;

        OpcodeStruct opStruct;
};


#endif // 