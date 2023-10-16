// __FileReader__

#include "../header/FileReader.h"


FileReader::FileReader()
{

}

FileReader::~FileReader()
{

}

void FileReader::readFile(std::string fileName)
{
    myFile.open(fileName);

    if(myFile.fail())
    {
 		std::cout << "Error opening the file : "  << std::endl;
		exit(1);
    }

}

void FileReader::writeFile(std::string fileName)
{
    outFile.open(fileName);
}


void FileReader::writeToFile(std::string value)
{
    outFile << value << "\t";
}

void FileReader::writeToFile(std::string value,std::string value2,std::string value3)
{
    outFile << value << "\t" << value2 << "\t" << value3 << "\t";
}

void FileReader::writeToFile(std::string value,std::string value2,std::string value3, std::string value4)
{
    outFile << value << "\t" << value2 << "\t" << value3 << "\t" << value4 << "\t";
}

void FileReader::newLine()
{
    outFile << "\n";
}



void FileReader::closeReadFile()
{
    myFile.close();
}
void FileReader::closeWriteFile()
{
    outFile.close();
}

