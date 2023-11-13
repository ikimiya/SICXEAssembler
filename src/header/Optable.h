// Optable.h 

#ifndef _OPTABLE_H_
#define _OPTABLE_H_


#include <string>
#include <iostream>
#include <map>

class Optable
{

    private: 


    public:

        Optable();

        ~Optable();

        void createTable();

        int getFormat(std::string Mnemonic);
        std::string getOpcode(std::string Mnemonic);

        bool checkOpExist(std::string Mnemonic);

        std::string checkSpecial(std::string Mnemonic);

        void debug();


        std::map<std::string, std::pair<int, std::string>> OPTABLE;

};

#endif