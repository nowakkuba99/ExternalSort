/* Includes */

/* User includes */
#include "fileWriter.hpp"
/* Functions bodies */

/*
 Function used to open file to read data from
 Arguments: File name, open mode
 Returns: OK/ERROR depnding on opening result
*/
bool fileWriter::openFile(const std::string fileName, OPEN_MODE fileOpenMode)
{
    if(outputFile.is_open()) //If some file already open -> close
    {
        closeFile();
        fileOpened = false;
    }
    outputFile.open((const std::string)(PATH + fileName), fileOpenMode);    //Open new file
    if(outputFile.is_open())
    {
        fileOpened = true;
        currentFileName = fileName;
        currentOutputMode = fileOpenMode;
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
bool fileWriter::closeFile()
{
    if(outputFile.is_open()) //If some file open -> close
    {
        outputFile.close();
        if(outputFile.is_open()) //If still opened report error
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
 Function used to wrtie from vector to file
 Arguments: Reference to vector to write from
 Returns: OK/ERROR depnding on opening result
*/
bool fileWriter::writeFromVector(std::vector<int>& dataToWrite)
{
    if(outputFile.is_open())    //If file open
    {
        for(auto const& value:dataToWrite)
        {
            outputFile<<value<<" ";     //Write data with " " as delimiter
        }
        return errorReportBlock.OK;
    }
    #ifdef DEBUG
    errorReportBlock.showError(errorReportBlock.OUTPUT_FILE_NOT_OPENED);
    #endif
    return errorReportBlock.OK;
}
/*
 Function used to wrtie from vector to file
 Arguments: Reference to vector to write from
 Returns: OK/ERROR depnding on opening result
*/
bool fileWriter::appendValueToFile(int* value)
{
    if(currentOutputMode == APPEND)
    {
        outputFile<<(*value)<<" "; //Append value to the file
    }
    else
    {
        #ifdef DEBUG
        errorReportBlock.showError(errorReportBlock.WRONG_FILE_MODE);
        #endif
        return errorReportBlock.ERROR;  //If block set as overwrite -> error
    }
    
    
    return errorReportBlock.OK;
}