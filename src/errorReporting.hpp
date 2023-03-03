#ifndef D837F4AD_8E66_41BB_80AD_EB02BF775238
#define D837F4AD_8E66_41BB_80AD_EB02BF775238
/* Include librarires*/
#include <iostream>

class errorReporting
{
/* Error realted stuff */
public:
    errorReporting(){};
    ~errorReporting(){};
    /* ERROR MESSAGES */
    const char* OUTPUT_FILE_NOT_OPENED = "Output file not specified - Write operation not possible!";
    const char* NO_DATA_READ = "No data was read from file - it might be empty!";
    const char* WRONG_FILE_MODE = "File is open in overwrite mode - not append!";
    const char* FILE_NAME_NOT_CHANGED = "File name was not changed!";
    const char* FILE_NOT_REMOVED = "File could not be removed - possible permission access!";
    const char* FILE_NOT_OPENED = "File could not be opened - possible permission access or wrong name!";
    const char* FILE_NOT_CLOSED = "File could not be closed!";
    const char* SOLVER_ERROR = "Problem was not solved - an error occured - see error logs!";
    /* ERROR DISPLAY FUNCTIONS */
    void showError(const char* errorMessage)
    {
        std::cout<<errorMessage<<"\n";
    }
    /* OTHER VARIABLES */
    enum STATUS
    {
        OK = true,
        ERROR = false
    };
    
};
#endif /* D837F4AD_8E66_41BB_80AD_EB02BF775238 */
