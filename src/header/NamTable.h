// NamTable.h 

#ifndef _NamTable_H_
#define _NamTable_H_


#include <string>
#include <iostream>
#include <map>

class NamTable
{
    private: 

    public:

        struct namLoc
        {
            int startIndex;
            int endIndex;
        };

        NamTable();

        ~NamTable();

        void insertTable(std::string Label, namLoc& nLoc);    

        std::string getName(std::string Label);
        int getStart(std::string Label);
        int getEnd (std::string Label);

        void setName(std::string label);
        void setStart(std::string label, int value);
        void setEnd(std::string label, int value);

        // check if exist
        bool checkTableExist(std::string Label);

        void resetTable();

        void debug();

        namLoc namTabLoc;

        std::map<std::string, struct namLoc> namTab;
};

#endif