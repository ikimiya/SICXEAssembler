// __ControlTab.cpp__

#include "../header/ControlTab.h"

ControlTab::ControlTab()
{

}

ControlTab::~ControlTab()
{

}

void ControlTab::insertTable(std::string label, cSectValue& literal)
{
    controlTable.insert (std::pair<std::string, cSectValue>(label,literal));
}

bool ControlTab::checkTableExist(std::string label)
{
    auto it = controlTable.find(label);
    return it != controlTable.end();
}

void ControlTab::setBeginAddress(std::string label, int value)
{
    auto it = controlTable.find(label);
    if (it != controlTable.end()) {
        it->second.beginAddress = value;
    } else {
        std::cout << "Begin Address Not Found with "<< label << std::endl;
    } 
}

void ControlTab::setEndAddress(std::string label, int value)
{
    auto it = controlTable.find(label);
    if (it != controlTable.end()) {
        it->second.endAddress = value;
    } else {
        std::cout << "End Address Not Found with "<< label << std::endl;
    } 
}

int ControlTab::getBeginAddress(std::string label)
{
    auto it = controlTable.find(label);
    if (it != controlTable.end()) {
        return it->second.beginAddress; 
    } else {
        return -1; 
    }
}

int ControlTab::getEndAddress(std::string label)
{
    auto it = controlTable.find(label);
    if (it != controlTable.end()) {
        return it->second.endAddress; 
    } else {
        return -1; 
    }
}

void ControlTab::resetTable()
{
    cSectTable.beginAddress = -1;
    cSectTable.endAddress = -1;
}

bool ControlTab::ifControl() {
    return !controlTable.empty() && controlTable.size() > 1;
}

void ControlTab::debug()
{
    for(auto it = controlTable.begin(); it != controlTable.end(); it++)
    {
        std::cout << "CSect Name: [" << it->first 
                  << "] beginAddress: [" << it->second.beginAddress 
                  << "] endAddress: [" << it->second.endAddress << "]\n";
    }
}