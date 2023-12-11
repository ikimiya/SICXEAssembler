// __Symtable.cpp__

#include "../header/Symtable.h"


Symtable::Symtable()
{
    this->quickInsert("A",0);
    this->quickInsert("X",1);
    this->quickInsert("L",2);
    this->quickInsert("PC",8);
    this->quickInsert("SW",9);
    this->quickInsert("B",3);
    this->quickInsert("S",4);
    this->quickInsert("T",5);
    this->quickInsert("F",6);
}

Symtable::~Symtable()
{

}

void Symtable::quickInsert(std::string label,int value)
{
    resetTable();

    if(checkTableExist(label))
    {
        // if exist dupe
    }
    else
    {
        infos.value = value;
        insertTable(label,infos);
    }
}

void Symtable::quickInsert(std::string label,int value,int bloc)
{
    resetTable();

    if(checkTableExist(label))
    {
        // if exist dupe
    }
    else
    {
        infos.value = value;
        infos.blockNumber = bloc;
        insertTable(label,infos);
    }
}

void Symtable::insertTable(std::string label, tableInfo& infos)
{
    SYMTABLE.insert(std::pair<std::string, tableInfo>(label,infos));
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
        return it->second.value; 
    } else {
        return -1; 
    }
}

void Symtable::setAddress(std::string label, int value)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        it->second.value = value;
    } else {
    }
}


void Symtable::setBlockAddress(std::string label, int address)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        it->second.value = address;
    } else {
        std::cout << "address not found" << std::endl;
    } 
}


std::string Symtable::getBlockName(std::string label)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second.blockName; 
    } else {
        return "null"; 
    }
}


int Symtable::getBlockAddress(std::string label)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second.address; 
    } else {
        return -1; 
    }
}

int Symtable::getBlockAddressIndex(int index)
{
    for (auto& it : SYMTABLE) {
        if (it.second.blockNumber == index) {
            return it.second.length;
        }
    }
    return -1;
}

int Symtable::getBlockLength(std::string label)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second.length; 
    } else {
        return -1; 
    }
}

int Symtable::getBlockNumber(std::string label)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second.blockNumber; 
    } else {
        return -1; 
    }
}

void Symtable::setBlockNumber(std::string label, int value)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        it->second.blockNumber = value;
    } else {
    }
}
void Symtable::setLength(std::string label, int value)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        it->second.length = value;
    } else {
    }
    
}
void Symtable::setDef(std::string label, int value)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        it->second.extDef = value;
    } else {
    }
}

void Symtable::setRef(std::string label, int value)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        it->second.extRef = value;
    } else {
    }
}

bool Symtable::getDef(std::string label)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second.extDef; 
    } else {
        return -1; 
    }
}

bool Symtable::getRef(std::string label)
{
    auto it = SYMTABLE.find(label);
    if (it != SYMTABLE.end()) {
        return it->second.extRef; 
    } else {
        return -1; 
    }
}


void Symtable::debug()
{
    //std::cout << "Testing: " << infos.blockName << std::endl;

    std::cout << "DEBUGGING: " << std::endl;
    for(auto it = SYMTABLE.begin(); it != SYMTABLE.end(); it++)
    {
        std::cout << "Symbol: [" << it->first
                  << "] value: [" << it->second.value 
                  << "] type: [" << it->second.type 
                  << "] blockNumber: [" << it->second.blockNumber 
                  << "] Address: [" << it->second.address 
                  << "] Length: [" << it->second.length 
                  << "] ExtDef: [" << it->second.extDef 
                  << "] ExtRef: [" << it->second.extRef 
                  << "]\n";
    }
    std::cout << "ENDDEBUG: " << std::endl;

}

void Symtable::resetTable()
{
    infos.type = "R";
    infos.value = 0;
    infos.blockName = "";
    infos.blockNumber = 0;
    infos.address = 0;
    infos.length = 0;
    infos.extDef = 0;
    infos.extRef = 0;
}