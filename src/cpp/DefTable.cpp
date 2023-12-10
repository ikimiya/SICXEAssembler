// __DefTable.cpp__

#include "../header/DefTable.h"

DefTable::DefTable()
{

}

DefTable::~DefTable()
{

}

void DefTable::insertTable(std::string label)
{
    defTab[counter] = label;
    counter++;
}

// Check Map duplicates
bool DefTable::checkTableExist(int index)
{
    auto it = defTab.find(index);
    // Check if the key exists
    return it != defTab.end();
}


std::string DefTable::getMacro(int index)
{
    auto it = defTab.find(index);
    if (it != defTab.end()) {
        return it->second;
    } else {
        return "Null";
    }
}


void DefTable::debug()
{

    for(auto it = defTab.begin(); it != defTab.end(); it++)
    {
        std::cout << "int: [" << it->first 
                  << "] stringstream.str(): [" << it->second << "]\n";
    }

    //std::cout <<  "test:" << DefTablele.begin()->second << std::endl;

}