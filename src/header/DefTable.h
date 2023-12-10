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

        void insertTable(std::stringstream word); 
        bool checkTableExist(int index);

        std::string getMacro(int index);

        std::map<int, std::stringstream> defTab;

        void debug();

        int counter = 0;

};

#endif