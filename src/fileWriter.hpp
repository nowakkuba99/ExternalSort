#ifndef AC9D18DD_4ED1_488D_A48B_5E4DC8EDC221
#define AC9D18DD_4ED1_488D_A48B_5E4DC8EDC221
/* Includes */
#include <vector>
/* User includes */
#include "fileActions.hpp"

class fileWriter: public fileActions
{
private:
    std::ofstream outputFile;    //The file to which the data will be written
public:
    /* Constructors */
    fileWriter() {};
    fileWriter(const std::string fileName, OPEN_MODE fileOpenMode)
    {
        outputFile.open((const std::string)(PATH + fileName), fileOpenMode);    //Open new file
        if(outputFile.is_open())
        {
            currentFileName = fileName;
            fileOpened = true;
        }
    }
    /* Destructor */
    ~fileWriter()
    {
        if(outputFile.is_open())
        {
            outputFile.close(); //Close file
        }
    };
    /* User defined functions - derived */
    bool openFile(const std::string fileName, OPEN_MODE fileOpenMode) override;
    bool closeFile() override;
    /* User defined functions - writer */
    bool writeFromVector(std::vector<int>& dataToWrite);    //Write to file from vector
    bool appendValueToFile(int* value);     //Write to file from int

};



#endif /* AC9D18DD_4ED1_488D_A48B_5E4DC8EDC221 */
