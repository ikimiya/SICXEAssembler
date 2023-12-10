// ArgTable.h 

#ifndef _ArgTable_H_
#define _ArgTable_H_

#include <string>
#include <iostream>
#include <map>

class ArgTable
{


    private: 


    public:

        ArgTable();

        ~ArgTable();

        void insertTable(std::string Label); 
        bool checkTableExist(std::string Label);
        bool checkTableExistInt(int index);


        void cleanTable();

        std::string getArg(int index);


        void debug();

        std::map<std::string, int> argTab;

};

#endif