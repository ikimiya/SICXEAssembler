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

        struct tableInfo{
            // A or R or E
            std::string type;
            // the address it is at
            int value;

            // blocks 
            std::string blockName;
            int blockNumber;
            int address;
            int length;

            // control sectrol
            bool extDef;
            bool extRef;

        };


        void quickInsert(std::string Label, int value);
        void quickInsert(std::string Label, int value, int bloc);

        bool checkTableExist(std::string Label);
        void setAddress(std::string label,int address);
        int getAddress(std::string Label);

        // blocks
        int getBlockNumber(std::string Label);
        int getBlockAddress(std::string Label);
        int getBlockLength(std::string Label);  
        int getBlockAddressIndex(int index);
        std::string getBlockName(std::string label);  

        void setBlockNumber(std::string Label, int value);
        void setBlockAddress(std::string Label, int value);
        void setLength(std::string Label, int value);

        // control section
        void setDef(std::string Label, int value);
        void setRef(std::string Label, int value);

        bool getDef(std::string label);
        bool getRef(std::string label);


        void insertTable(std::string Label, tableInfo &infos);
        void resetTable();
        void debug();

        //void insertTable(std::string Label, int address);    

        // finds address

        // check if exist

        tableInfo infos;


        std::map<std::string, struct tableInfo> SYMTABLE;



};

#endif