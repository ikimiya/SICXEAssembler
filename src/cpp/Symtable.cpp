// __Symtable.cpp__

#include "../header/Symtable.h"


Symtable::Symtable()
{
    SYMTABLE.insert (std::pair<std::string, int>("A",0));
    SYMTABLE.insert (std::pair<std::string, int>("X",1));
    SYMTABLE.insert (std::pair<std::string, int>("L",2));
    SYMTABLE.insert (std::pair<std::string, int>("PC",8));
    SYMTABLE.insert (std::pair<std::string, int>("SW",9));
    SYMTABLE.insert (std::pair<std::string, int>("B",3));
    SYMTABLE.insert (std::pair<std::string, int>("S",4));
    SYMTABLE.insert (std::pair<std::string, int>("T",5));
    SYMTABLE.insert (std::pair<std::string, int>("F",6));
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
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second; 
    } else {
        return -1; 
    }
}

void Symtable::debug()
{

    for(auto it = SYMTABLE.begin(); it != SYMTABLE.end(); it++)
    {
        std::cout << "IT: " << it->first << ", "<< it->second << std::endl;

    }

    std::cout <<  "test" << SYMTABLE.begin()->second << std::endl;

}