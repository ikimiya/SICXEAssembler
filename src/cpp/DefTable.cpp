// __DefTable.cpp__

#include "../header/DefTable.h"

DefTable::DefTable()
{

}

DefTable::~DefTable()
{

}

void DefTable::insertTable(std::stringstream label)
{
    defTab[counter] << label.str();
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
        return it->second.str();
    } else {
        return "Null";
    }
}


void DefTable::debug()
{

    for(auto it = defTab.rbegin(); it != defTab.rend(); it++)
    {
        std::cout << "int: [" << it->first 
                  << "] stringstream.str(): [" << it->second.str() << "]\n";
    }

    //std::cout <<  "test:" << DefTablele.begin()->second << std::endl;

}