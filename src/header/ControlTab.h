// ControlTab.h 

#ifndef _ControlTab_H_
#define _ControlTab_H_


#include <string>
#include <iostream>
#include <map>

class ControlTab
{
    private: 
    public:


        struct cSectValue
        {
            int beginAddress;
            int endAddress;
        };

        ControlTab();

        ~ControlTab();

        void insertTable(std::string Label, cSectValue& literal);    

        int getBeginAddress(std::string Label);
        int getEndAddress(std::string Label);    

        void setBeginAddress(std::string Label, int value);
        void setEndAddress(std::string Label, int value);


        // check if exist
        bool checkTableExist(std::string Label);

        bool ifControl();

        void resetTable();

        void debug();

        cSectValue cSectTable;

        std::map<std::string, struct cSectValue> controlTable;

};

#endif