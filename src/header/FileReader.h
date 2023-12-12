// FileReader.h 

#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <iostream>
#include <string>
#include <fstream>

class FileReader
{

    public:
        FileReader();

        ~FileReader();

        // reads file
        void readFile(std::string fileName);

        // write File
        void writeFile(std::string fileName);

        // write to file no tab
        void writeToFileNoTab(std::string word);
        
        // write to file outfit has tab
        void writeToFile(std::string word);
        void writeToFile(std::string word, std::string word2, std::string word3);
        void writeToFile(std::string word, std::string word2, std::string word3, std::string word4);

        // write a tab
        void writeToFileTab();

        void newLine();

        void closeReadFile();
        void closeWriteFile();

        bool fileNotExist = false;
        std::ifstream myFile;
        std::ofstream outFile;
};


#endif 