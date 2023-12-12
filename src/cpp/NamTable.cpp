// __NamTable.cpp__

#include "../header/NamTable.h"

NamTable::NamTable()
{

}

NamTable::~NamTable()
{

}

void NamTable::insertTable(std::string label, namLoc& nLoc)
{
    namTab.insert(std::pair<std::string, namLoc>(label,nLoc));
}

bool NamTable::checkTableExist(std::string label)
{
    auto it = namTab.find(label);
    return it != namTab.end();
}

std::string NamTable::getName(std::string label)
{
    auto it = namTab.find(label);
    if (it != namTab.end()) {
        return it->first; 
    } else {
        return "null"; 
    }
}

int NamTable::getStart(std::string label)
{
    auto it = namTab.find(label);
    if (it != namTab.end()) {
        return it->second.startIndex; 
    } else {
        return -1; 
    }
}

int NamTable::getEnd(std::string label)
{
    auto it = namTab.find(label);
    if (it != namTab.end()) {
        return it->second.endIndex; 
    } else {
        return -1; 
    }
}

void NamTable::setStart(std::string label, int value)
{
    auto it = namTab.find(label);
    if (it != namTab.end()) {
        it->second.startIndex = value;
    } else {
    }
}
void NamTable::setEnd(std::string label, int value)
{
    auto it = namTab.find(label);
    if (it != namTab.end()) {
        it->second.endIndex = value;
    } else {
    }
}

void NamTable::resetTable()
{
    namTabLoc.startIndex = -1;
    namTabLoc.endIndex = -1;
}

void NamTable::debug()
{
    for(auto it = namTab.rbegin(); it != namTab.rend(); it++)
    {
        std::cout << "Macro Name: [" << it->first 
                  << "] Starting Loc: [" << it->second.startIndex 
                  << "] Ending Loc: [" << it->second.endIndex << "]\n";
    }
}