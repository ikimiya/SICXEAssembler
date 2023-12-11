// blockTable.h 

#ifndef _blockTable_H_
#define _blockTable_H_


#include <string>
#include <iostream>
#include <map>

class BlockTable
{


    private: 

    public:


        struct blocks
        {
            int blockNumber;
            int address;
            int length;
        };

        BlockTable();

        ~BlockTable();

        void insertTable(std::string Label, blocks& blockT);    

        // finds address
        int getBlockNumber(std::string Label);
        int getAddress(std::string Label);
        int getLength(std::string Label);  
        int getLengthIndex(int index);
        int getAddressIndex(int index);
        int getHighestBlock();


        std::string getBlockName(std::string label);  


        void setBlockNumber(std::string Label, int value);
        void setAddress(std::string Label, int value);
        void setLength(std::string Label, int value); 

        // check if exist
        bool checkTableExist(std::string Label);

        void resetTable();

        void debug();

        blocks bTable;

        std::map<std::string, struct blocks> blockTable;

};

#endif