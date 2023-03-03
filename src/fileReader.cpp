/* Includes */

/* User includes */
#include "fileReader.hpp"
/* Functions bodies */

/*
 Function used to open file to read data from
 Arguments: File name, open mode (optional)
 Returns: OK/ERROR depnding on opening result
*/
bool fileReader::openFile(const std::string fileName, OPEN_MODE fileOpenMode)
{
    if(inputFile.is_open()) //If some file already open -> close
    {
        closeFile();
        fileOpened = false;
    }
    inputFile.open((const std::string)(PATH + fileName), fileOpenMode);    //Open new file
    if(inputFile.is_open())
    {
        fileOpened = true;
        currentFileName = fileName;
        return errorReportBlock.OK;
    }
    else
    {
        #ifdef DEBUG
        errorReportBlock.showError(errorReportBlock.FILE_NOT_OPENED);
        #endif
        return errorReportBlock.ERROR;
    }
}
/*
 Function used to close file to read data from
 Arguments: -
 Returns: OK/ERROR depnding on opening result
*/
bool fileReader::closeFile()
{
    if(inputFile.is_open()) //If some file open -> close
    {
        inputFile.close();
        if(inputFile.is_open()) //If still opened report error
        {
            #ifdef DEBUG
            errorReportBlock.showError(errorReportBlock.FILE_NOT_CLOSED);
            #endif
            return errorReportBlock.ERROR;
        }
        else
        {
            fileOpened = false;
            return errorReportBlock.OK;
        }
        
    }
    else    //If no file open -> report error
    {
        #ifdef DEBUG
        errorReportBlock.showError(errorReportBlock.FILE_NOT_CLOSED);
        #endif
        return errorReportBlock.ERROR;
    }
}

/*
 Function used to read data to vector data structure of decleared size (max memory size)
 Arguments: Reference to vector to store data, amount of data to read
*/
bool fileReader::readToVector(std::vector<int>& dataStore, int amountToRead)
{
    if(inputFile.is_open())
    {
        std::string currVal;    //Variable to store current int as string
        int count = 0;  //Count number of read int's
        for(int i = 0;i<amountToRead; i++)  //Read specified block size
        {
            if(std::getline(inputFile,currVal,' '))    //Get 1 number with space as delimiter
            {
                dataStore.push_back(std::stoi(currVal));    //Push back int to vector
                count++;    //Increment count value
            }
            else    //If nothing read -> break
                break;
        }
        if(count > 0)
            return errorReportBlock.OK;
        else    //If no data read -> report error
        {
            #ifdef DEBUG
            errorReportBlock.showError(errorReportBlock.NO_DATA_READ);
            #endif
            //closeFile();
            return errorReportBlock.ERROR;
        }
    }
    else
    {
        #ifdef DEBUG
        errorReportBlock.showError(errorReportBlock.NO_DATA_READ);
        #endif
        return errorReportBlock.ERROR;
    }
}
/*
 Function used to read data to int variable
 Arguments: Reference to int variable
*/
bool fileReader::readToInt(int& dataStore)
{
    if(inputFile.is_open())
    {
        std::string currVal;    //Variable to store current int as string
        int count = 0;  //Count number of read int's
        if(std::getline(inputFile,currVal,' '))    //Get 1 number 
        {
            dataStore = std::stoi(currVal);    //Set value to dataStore
            count++;    //Increment count value
        }
        if(count > 0)
            return errorReportBlock.OK;
        else    //If no data read -> report error
        {
            #ifdef DEBUG
            errorReportBlock.showError(errorReportBlock.NO_DATA_READ);
            #endif
            //closeFile();
            return errorReportBlock.ERROR;
        }
    }
    else
    {
        #ifdef DEBUG
        errorReportBlock.showError(errorReportBlock.NO_DATA_READ);
        #endif
        return errorReportBlock.ERROR;
    }
}