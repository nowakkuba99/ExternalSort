#ifndef B2F76E8A_CE73_4AB8_8259_3D87D77F6E13
#define B2F76E8A_CE73_4AB8_8259_3D87D77F6E13
/* Includes */
#include <fstream>
/* User includes */
#include "errorReporting.hpp"
/* Defines for debug mode */
//#define DEBUG
/* Define path where files will be located */
static const std::string PATH = "../resources/";
class fileActions
{
public:
    typedef enum OPEN_MODE
    {
        OVERWRITE = std::ofstream::out,
        APPEND = std::ofstream::app,
        READ = std::ifstream::in,
        NOT_SET
    } OPEN_MODE;
protected:
    std::string currentFileName;       //Variable to store the name of current file
    errorReporting errorReportBlock;    //Object handing error reporting
    OPEN_MODE currentOutputMode = NOT_SET;    //Variable to store current output mode
    bool fileOpened = false;            //Variable to store information about file state
public:
    /* Virtual functions */
    virtual bool openFile(const std::string fileName, OPEN_MODE fileOpenMode) = 0;
    virtual bool closeFile() = 0;
    /* Other functions */
    bool renameFile(std::string newName)
    {
        if(fileOpened == false && currentFileName != "")
        {
            int result = std::rename((PATH + currentFileName).c_str(),(PATH + newName).c_str());
            if(result == 0)
                return errorReportBlock.OK;
            else
            {
                #ifdef DEBUG
                errorReportBlock.showError(errorReportBlock.FILE_NAME_NOT_CHANGED);
                #endif
                return errorReportBlock.ERROR;
            }
        }
        else
        {
            #ifdef DEBUG
            errorReportBlock.showError(errorReportBlock.FILE_NAME_NOT_CHANGED);
            #endif
            return errorReportBlock.ERROR;
        }
    }
    bool removeFile()
    {
        if(fileOpened == false && currentFileName != "")
        {
            int result = std::remove((PATH + currentFileName).c_str());
            if(result == 0)
            {
                return errorReportBlock.OK;
            }
            else
            {
                #ifdef DEBUG
                errorReportBlock.showError(errorReportBlock.FILE_NOT_REMOVED);
                #endif
                return errorReportBlock.ERROR;
            }
        }
        else
        {
            #ifdef DEBUG
            errorReportBlock.showError(errorReportBlock.FILE_NOT_REMOVED);
            #endif
            return errorReportBlock.ERROR;
        }
    }
};


#endif /* B2F76E8A_CE73_4AB8_8259_3D87D77F6E13 */
