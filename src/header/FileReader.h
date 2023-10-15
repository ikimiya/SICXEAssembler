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

        void readFile();

        void writeFile();

        void setFileName(const char* fileName);

        const char* fileName;

};


#endif 