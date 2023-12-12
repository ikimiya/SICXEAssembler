// main.cpp

#include <iostream>
#include <filesystem>

#include "src/header/Pass1.h"
#include "src/header/Pass2.h"


void genObj(std::string fileName)
{
    Pass1 p1;
    Pass2 p2;

    std::cout << "[Running: " << fileName << ".txt].." << std::endl;
    p1.setFileName(fileName);

    if(p1.fReader.fileNotExist)
    {
        std::cout << "[Aborting Error File Name: " << fileName << ".txt]....." << std::endl;
        std::cout << " " << std::endl;
    }
    else
    {
        p1.beginPass1();
        p2.setFileName(fileName);
        p2.setOptable(p1.OPTABLE);
        p2.setSymtable(p1.symTable);
        p2.setLiteralTab(p1.literalTable);
        p2.setBlockTab(p1.blockTABLE);
        p2.setControlTab(p1.conTable);
        p2.getPassData(p1.startAdd,p1.LocCtr,p1.programLength);
        p2.setLocation(p1.currentLoc,p1.pcLoc);
        p2.beginPass2();
        std::cout << "[Finish: " << fileName << ".txt].....\n" << std::endl;
    }
}

void genSingleFile(std::string fileName)
{
    Pass1 p1;
    Pass2 p2;
    //
    std::cout << "Running: " << fileName << ".txt" << std::endl;
    p1.setFileName(fileName);

    if(p1.fReader.fileNotExist)
    {
        std::cout << "Aborting Error File Name: " << fileName << ".txt" << std::endl;
    }
    else
    {
        p1.beginPass1();
        p2.setFileName(fileName);
        p2.setOptable(p1.OPTABLE);
        p2.setSymtable(p1.symTable);
        p2.setLiteralTab(p1.literalTable);
        p2.setBlockTab(p1.blockTABLE);
        p2.setControlTab(p1.conTable);
        p2.getPassData(p1.startAdd,p1.LocCtr,p1.programLength);
        p2.setLocation(p1.currentLoc,p1.pcLoc);
        p2.beginPass2();
        std::cout << "Ending: " << fileName << ".txt" << std::endl;
    }
}

int main()
{

    Symtable sym;

    std::string path = "Input";
    std::string resultPath;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        resultPath = entry.path().stem().u8string();
        genObj(resultPath);
    }

    /*
    fileName: basic.txt
    fileName = basic
    */ 
    //std::string fileName = "functions";
    //genSingleFile(fileName);

    std::cout << "Program Finished" << std::endl;

}