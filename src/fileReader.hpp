#ifndef BBD94052_0B9E_4A77_B243_6C484201C65B
#define BBD94052_0B9E_4A77_B243_6C484201C65B
/* Includes */
#include <vector>
/* User includes */
#include "fileActions.hpp"

class fileReader: public fileActions
{
private:
    std::ifstream inputFile;    //The file from which the data will be read
public:
    /* Constructors */
    fileReader() {};
    fileReader(const std::string fileName)
    {
        inputFile.open((const std::string)(PATH + fileName), std::fstream::in);    //Open new file
        if(inputFile.is_open())
        {
            currentFileName = fileName;
            fileOpened = true;
        }
    }
    /* Destructor */
    ~fileReader() 
    {
        if(inputFile.is_open())
        {
            inputFile.close();  //Close file 
        }
    };

    /* User defined functions - derived */
    bool openFile(const std::string fileName, OPEN_MODE fileOpenMode = fileActions::OPEN_MODE::READ) override;
    bool closeFile() override;
    /* User defined functions - reader */
    bool readToVector(std::vector<int>& dataStore, int amountToRead);     //Read from file into vector the size of defined block
    bool readToInt(int& dataStore);     //Read from file to int
};


#endif /* BBD94052_0B9E_4A77_B243_6C484201C65B */
