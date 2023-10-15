// __Symtable.cpp__

#include "../header/Symtable.h"


Symtable::Symtable()
{

}

Symtable::~Symtable()
{

}

void Symtable::insertTable(std::string label, int value)
{
    SYMTABLE.insert (std::pair<std::string, int>(label,value));
}

// Check Map duplicates
bool Symtable::checkTableExist(std::string label)
{

    // Map does not allow duplicates
    bool exist = false;

    if(SYMTABLE.find(label) == SYMTABLE.end())
    {
        return false;
    }
    else
    {
        return true;
    }

    return false;
}


int Symtable::getAddress(std::string label)
{
    int temp = SYMTABLE.at(label);
    return temp;
}

void Symtable::debug()
{

    for(auto it = SYMTABLE.begin(); it != SYMTABLE.end(); it++)
    {
        std::cout << "IT: " << it->first << it->second << std::endl;

    }

}