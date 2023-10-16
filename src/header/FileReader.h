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

        void writeToFile(std::string word);

        void writeToFile(std::string word, std::string word2, std::string word3);

        void writeToFile(std::string word, std::string word2, std::string word3, std::string word4);

        void newLine();

        void closeReadFile();

        void closeWriteFile();


        std::ifstream myFile;

        std::ofstream outFile;

};


#endif 