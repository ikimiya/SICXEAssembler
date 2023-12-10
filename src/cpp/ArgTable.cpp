// __ArgTable.cpp__

#include "../header/ArgTable.h"

ArgTable::ArgTable()
{

}

ArgTable::~ArgTable()
{

}

void ArgTable::insertTable(std::string label, int value)
{
    argTab[label] = value;
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
    for (const auto& entry : argTab) {
        if (entry.second == index) {
            return true;
        }
    }
    return false;
}

std::string ArgTable::getArg(int index)
{
    for (const auto& entry : argTab) {
        if (entry.second == index) {
            return entry.first;
        }
    }
    return "NULL";
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