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

        std::vector<std::string> indexList;
        std::vector<std::string> LabelList;
        std::vector<std::string> OpCodeList;
        std::vector<std::string> OperandList;
        std::vector<std::string> CommentList;
        
        std::vector<bool> errorFlag;
        std::vector<bool> symbolFlag;


        std::vector<std::pair<int,int>> currentLoc;
        std::vector<std::pair<int,int>> pcLoc;
        int counter = 0;
        int blockCounter = 0;
        int blockCtr = 0;
        std::string blockName;



        bool errorF;
        bool symbolF;

        std::vector<std::string> literalDupe;

        Symtable symTable;
        Optable OPTABLE;
        Libtab literalTable;
        BlockTable blockTABLE;

        // csect
        std::string controlName;


        //Macros
        ArgTable argTab;
        DefTable defTab;
        NamTable namTab;

        int macroCounter = 0;
        bool macroExist = false;

        std::vector<std::string> notation;
        bool expanding;



        FileReader fReader;
        Conversion converter;

        std::string fileName;

        std::stringstream ss;
        std::string currentLine; 
        std::string Label, OpCode, Operand, Comment;
        
        int startAdd;
        int LocCtr;
        int programLength;




};


#endif // 