// __Pass2.cpp__

#include "../header/Pass2.h"


Pass2::Pass2()
{

}

Pass2::~Pass2()
{

}

void Pass2::setFileName(std::string fileName_)
{
    fileName = fileName_;
    fReader.readFile("Immediate/" + fileName + "testIMT.txt");

}

void Pass2::beginPass2()
{

    std::cout << "begin pass2 :" << std::endl;

    fReader.writeFile("Result/" + fileName + "result.txt");

    if(fReader.myFile.is_open())
    {
        // get first line from intermediate
        std::getline(fReader.myFile,currentLine);
        ss << currentLine;

        std::getline(ss, Address, '\t');
        std::getline(ss, Label, '\t');
        std::getline(ss, OpCode, '\t');
        std::getline(ss, Operand, '\t');


        std::cout << "Address:" << std::endl;

        if(OpCode == "START")
        {
            // write something
            fReader.writeToFile(converter.decimalToHexFour(Address));
            fReader.newLine();

            // read next input line
            readNextInput();

        }   // end if start


        // write header
        writeHeader();
        // initalize text record


        while(OpCode != "END")
        {

            // if it is not comment line 
            if(Label[0] != '.')
            {
                // search table for op code
                if(OPTABLE.checkOpExist(OpCode))
                {
                    
                    if(Label != "")
                        {
                            if(symTable.checkTableExist(Operand))
                            {
                                //std::cout << "testing: Duplicated Symbol Found" << std::endl;
                                symbolAddress = symTable.getAddress(Operand);

                            }else
                            {   
                                //std::cout << "inserted in " ;
                                symbolAddress = 0;
                                std::cout << "Set Error Flag Undefined Symbol" << std::endl;
                                
                            }

                    }// end if symbol

                    symbolAddress = 0;
                    // calculate Object code
                    
                }else if (OpCode == "BYTE" || OpCode == "WORD")
                {
                    // convert to object code with constants

                }


                /*
                // check code counter
                if object code is >= 10 * 3, 
                    create new text record
                else
                add object cord to text record


                */
               

            } // end if not comment


            /*
                Write listening line 
                
            
            */
           readNextInput();

        }   // end while nmot end 

        // write text to Text object program

        // write end record 

        //write last listing line




    }   // end myfile is open

}

void Pass2::writeHeader()
{
    // Need to check Label length of 6
    std::string programName = "H"+Label;
    std::string startingAddress = "00"+converter.binaryToHexByte(startAdd);
    std::string objectLength = "00"+converter.binaryToHexByte(programLength);

    fReader.writeToFile(programName);
    fReader.writeToFileNoTab(startingAddress);
    fReader.writeToFileNoTab(objectLength);
    fReader.newLine();

}

void Pass2::getPassData(int starting, int loc, int pLength)
{
    startAdd = startAdd;
    //LocCtr = loc;
    programLength = pLength;
}

void Pass2::readNextInput()
{

    std::getline(fReader.myFile,currentLine);
    ss.clear();
    ss.str(std::string());
    ss << currentLine;
    std::getline(ss, Address, '\t');
    std::getline(ss, Label, '\t');
    std::getline(ss, OpCode, '\t');
    std::getline(ss, Operand, '\t');

}


void Pass2::setOptable(Optable op)
{
    OPTABLE = op;
}

void Pass2::setSymtable(Symtable sym)
{
    symTable = sym;
}