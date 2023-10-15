// main.cpp

#include <iostream>
#include <map>

std::map<std::string, std::pair<int, std::string>> OPTABLE;

void createOPTABLE()
{
    OPTABLE["Test"] = std::make_pair(3, "18");



}



int main()
{

    std::string test = "Test";

    createOPTABLE();
    std::cout << "test word" << std::endl;



    std::cout << OPTABLE[test].first << " " << OPTABLE[test].second << std::endl;








}