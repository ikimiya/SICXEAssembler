// Symtable.h 

#ifndef _Symtable_H_
#define _Symtable_H_


#include <string>
#include <iostream>
#include <map>

class Symtable
{


    private: 


    public:

        Symtable();

        ~Symtable();

        void insertTable(std::string Label, int address);    

        // finds address
        int getAddress(std::string Label);

        // check if exist
        bool checkTableExist(std::string Label);

        void debug();

        std::map<std::string, int> SYMTABLE;

};

#endif