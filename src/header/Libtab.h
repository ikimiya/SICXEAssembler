// Libtab.h 

#ifndef _Libtab_H_
#define _Libtab_H_

#include <string>
#include <iostream>
#include <map>

class Libtab
{
    private: 

    public:
        struct libValue
        {
            std::string operand;
            std::string length;
            std::string address;
        };

        Libtab();
        ~Libtab();

        void insertTable(std::string Label, libValue& literal);    

        // finds address
        std::string getOperand(std::string Label);
        std::string getAddress(std::string Label);
        std::string getLength(std::string Label);        

        // check if exist
        bool checkTableExist(std::string Label);

        void resetTable();
        void debug();

        libValue literalTable;

        std::map<std::string, struct libValue> libTable;
};

#endif