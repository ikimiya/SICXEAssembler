// __GenerateOp.h__
// Generates objectCode


#ifndef __GENERATEOP_H_
#define __GENERATEOP_H_

#include <iostream>
#include <string>
#include <sstream>


class GenerateOp
{
    public:
        GenerateOp();

        ~GenerateOp();


        void setObject(int format, std::string oCode);

        void createObjectCode();

        void checkFormat();
        






        int format; 
        std::string objectCode;
        std::stringstream ss;


        bool n,i,x,b,p,e;



        /*
        PC = Next

        Base = Base
        
        
        */







};

#endif // !__GENERATEOP_H_