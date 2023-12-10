// __ArgTable.cpp__

#include "../header/ArgTable.h"

ArgTable::ArgTable()
{

}

ArgTable::~ArgTable()
{

}

void ArgTable::insertTable(std::string label)
{
    argTab[label];
}

// Check Map duplicates
bool ArgTable::checkTableExist(std::string label)
{
    auto it = argTab.find(label);
    // Check if the key exists
    return it != argTab.end();
}


bool ArgTable::checkTableExistInt(int index)
{
    auto it = argTab.find("");
    if (it != argTab.end() && it->second == index) {
        return true; 
    } else {
        return false; 
    }
}

std::string ArgTable::getArg(int index)
{
    auto it = argTab.find("");
    if (it != argTab.end() && it->second == index) {
        return it->first; 
    } else {
        return "NULL"; 
    }
}

void ArgTable::cleanTable()
{
    argTab.clear();
}



void ArgTable::debug()
{

    for(auto it = argTab.rbegin(); it != argTab.rend(); it++)
    {
        std::cout << "String: [" << it->first 
                  << "] index: [" << it->second << "]\n";
    }

    //std::cout <<  "test:" << ArgTablele.begin()->second << std::endl;

}