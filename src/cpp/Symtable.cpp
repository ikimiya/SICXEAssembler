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
    auto it = SYMTABLE.find(label);

    // Check if the key exists
    return it != SYMTABLE.end();
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
        std::cout << "IT: " << it->first << ", "<< it->second << std::endl;

    }

    std::cout <<  "test" << SYMTABLE.begin()->second << std::endl;

}