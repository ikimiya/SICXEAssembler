// __Pass2.h__

#ifndef __PASS2_H__
#define __PASS2_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "../header/Symtable.h"
#include "../header/FileReader.h"
#include "../../Math/Conversion.h"
#include "../header/Optable.h"

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

        void writeHeader();

        Optable getOptable(Optable op);
        Symtable getSymtable(Symtable sym);

        void getPassData(int starting, int loc, int pLength);

        void debug();

        std::vector<std::string> indexList;
        std::vector<std::string> LabelList;
        std::vector<std::string> OpCodeList;
        std::vector<std::string> OperandList;
        std::vector<std::string> CommentList;

       

        Symtable symTable;
        Optable OPTABLE;

        FileReader fReader;
        Conversion converter;

        std::string fileName;

        std::string currentLine; 
        std::string Address, Label, OpCode, Operand;
        std::stringstream ss;
        
        int startAdd;
        int LocCtr;
        int programLength;

        int symbolAddress;

};


#endif // 