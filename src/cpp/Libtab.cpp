// __Libtab.cpp__

#include "../header/Libtab.h"

Libtab::Libtab()
{

}

Libtab::~Libtab()
{

}

void Libtab::insertTable(std::string label, libValue& literal)
{
    libTable.insert (std::pair<std::string, libValue>(label,literal));
}

// Check Map duplicates
bool Libtab::checkTableExist(std::string label)
{
    auto it = libTable.find(label);

    // Check if the key exists
    return it != libTable.end();
}

std::string Libtab::getAddress(std::string label)
{
    auto it = libTable.find(label);
    if (it != libTable.end()) {
        return it->second.address; 
    } else {
        return "-1"; 
    }
}

std::string Libtab::getLength(std::string label)
{
    auto it = libTable.find(label);
    if (it != libTable.end()) {
        return it->second.length; 
    } else {
        return "-1"; 
    }
}

std::string Libtab::getOperand(std::string label)
{
    auto it = libTable.find(label);
    if (it != libTable.end()) {
        return it->second.operand; 
    } else {
        return "-1"; 
    }
}

void Libtab::resetTable()
{
    literalTable.address = "-1";
    literalTable.operand = "-1";
    literalTable.length = "-1";

}


void Libtab::debug()
{

    for(auto it = libTable.begin(); it != libTable.end(); it++)
    {
        std::cout << "Literal Name: " << it->first << "\n"
                  << "Operand: " << it->second.operand << "\n"
                  << "Length: " << it->second.length << "\n"
                  << "Address: " << it->second.address << "\n\n";

    }

    //std::cout <<  "test:" << libTable.begin()->second << std::endl;

}