// __Pass1.h__

#ifndef __PASS1_H__
#define __PASS1_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "../header/Symtable.h"
#include "../header/Libtab.h"
#include "../header/FileReader.h"
#include "../../Math/Conversion.h"
#include "../header/Optable.h"
#include "../header/blockTable.h"
#include "../header/ArgTable.h"
#include "../header/NamTable.h"
#include "../header/DefTable.h"
#include "../header/ControlTab.h"

class Pass1
{   
    
    public:
        
        Pass1();
        ~Pass1();


        void setFileName(std::string fileName);
        void beginPass1();
        void readNextInput();
        Optable getOptable();

        void debug();

        // errorFlag, symbolFlag
        std::vector<bool> errorFlag;
        std::vector<bool> symbolFlag;
        bool errorF;
        bool symbolF;

        // current and NextLocations
        std::vector<std::pair<int,int>> currentLoc;
        std::vector<std::pair<int,int>> pcLoc;
        int counter = 0;

        // block 
        std::string blockName;
        int blockCounter = 0;
        int blockCtr = 0;

        // literals
        std::vector<std::string> literalDupe;

        // tables
        Symtable symTable;
        Optable OPTABLE;
        Libtab literalTable;
        BlockTable blockTABLE;
        ControlTab conTable;
        ArgTable argTab;
        DefTable defTab;
        NamTable namTab;

        // csect
        std::string controlName;

        //Macros
        std::vector<std::string> notation;
        bool expanding;

        // fileReader and string converter
        FileReader fReader;
        Conversion converter;
        std::string fileName;

        // file parser
        std::stringstream ss;
        std::string currentLine; 
        std::string Label, OpCode, Operand, Comment;
        
        // starting address, location counter, program length
        int startAdd;
        int LocCtr;
        int programLength;
};


#endif // 