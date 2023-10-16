// __Pass1.h__

#ifndef __PASS1_H__
#define __PASS1_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "../header/Symtable.h"
#include "../header/FileReader.h"
#include "../../Math/Conversion.h"
#include "../header/Optable.h"

class Pass1
{   
    
    public:
        
        Pass1();
        ~Pass1();

        void setFileName(std::string fileName);

        void beginPass1();

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

        int startAdd;
        int LocCtr;
        int programLength;



};


#endif // 