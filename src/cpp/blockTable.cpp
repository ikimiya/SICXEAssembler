// __BlockTable.cpp__

#include "../header/blockTable.h"

BlockTable::BlockTable()
{

}

BlockTable::~BlockTable()
{

}

void BlockTable::insertTable(std::string label, blocks& block)
{
    blockTable.insert (std::pair<std::string, blocks>(label,block));
}

// Check Map duplicates
bool BlockTable::checkTableExist(std::string label)
{
    auto it = blockTable.find(label);

    // Check if the key exists
    return it != blockTable.end();
}

std::string BlockTable::getBlockName(std::string label)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        return it->first; 
    } else {
        return "null"; 
    }
}


int BlockTable::getAddress(std::string label)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        return it->second.address; 
    } else {
        return -1; 
    }
}

int BlockTable::getAddressIndex(int index)
{
    for (auto& it : blockTable) {
        if (it.second.blockNumber == index) {
            return it.second.address;
        }
    }
    
    return -1;
}

int BlockTable::getLength(std::string label)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        return it->second.length; 
    } else {
        return -1; 
    }
}

int BlockTable::getBlockNumber(std::string label)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        return it->second.blockNumber; 
    } else {
        return -1; 
    }
}


void BlockTable::setAddress(std::string label, int value)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        it->second.address = value;
    } else {
    }
}
void BlockTable::setBlockNumber(std::string label, int value)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        it->second.blockNumber = value;
    } else {
    }
}
void BlockTable::setLength(std::string label, int value)
{
    auto it = blockTable.find(label);
    if (it != blockTable.end()) {
        it->second.length = value;
    } else {
    }
    
}

void BlockTable::resetTable()
{
    bTable.blockNumber = -1;
    bTable.address = -1;
    bTable.length = -1;

}


void BlockTable::debug()
{

    for(auto it = blockTable.rbegin(); it != blockTable.rend(); it++)
    {
        std::cout << "Block Name: [" << it->first 
                  << "] blockNumber: [" << it->second.blockNumber 
                  << "] Address: [" << it->second.address 
                  << "] Length: [" << it->second.length << "]\n";
    }

    //std::cout <<  "test:" << BlockTablele.begin()->second << std::endl;

}