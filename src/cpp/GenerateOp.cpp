// __GenerateOp.cpp

#include "../header/GenerateOp.h"


GenerateOp::GenerateOp()
{

}


GenerateOp::~GenerateOp()
{

}

void GenerateOp::setObject(int format_, std::string oCode)
{
    format = format_;
    objectCode = oCode;

    checkFormat();

}

void GenerateOp::checkFormat()
{

    // check bits

    /*
    

    @ = n = 1, i = 0
    # = n = 0, i = 1
    else n = 1, i = 1
    if + then e = 1
    if there is ,X then x = 1

    PC
    1. Check pc after formula range

    2. check B after formula range    
    
    */

}

void GenerateOp::createObjectCode()
{


    

}