// DefTable.h 

#ifndef _DefTable_H_
#define _DefTable_H_

#include <string>
#include <iostream>
#include <map>
#include <sstream>

class DefTable
{
    private: 

    public:

        DefTable();

        ~DefTable();

        void insertTable(std::string word); 
        bool checkTableExist(int index);

        std::string getMacro(int index);

        std::map<int, std::string> defTab;

        void debug();
        int counter = 0;
};

#endif