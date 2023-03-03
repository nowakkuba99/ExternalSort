#ifndef CEB7FFC6_CAB5_4EC7_92DD_315076B1D2AC
#define CEB7FFC6_CAB5_4EC7_92DD_315076B1D2AC
/* Includes */

/* User includes */
#include "fileReader.hpp"
#include "fileWriter.hpp"

class solver
{
private:
    static const int BLOCK_SIZE = 2;   //Set the size of one block of data
    errorReporting errorReportBlock;    //Object handing error reporting
    fileReader inputFileA;      //Two input file objects used for merging sorted blocks
    fileReader inputFileB;      
    fileWriter outputFile;      //Output file object used to write sorted data
    unsigned long blockCounter = 0; //Counter of current block that is being processed
    unsigned long numberOfBlocks = 0;   //Current number of blocks
public:
    /* Constructor and destructor */
    solver(const std::string inputFileName);
    ~solver() {};
    /* Functions */
    bool sortIntoInitialPartitions();   //Divides input file into blocks and sorts all individual input files
    bool mergeSortedBlocks();   //Merges sorted blocks into single file
    static bool solve();   //Function to solve the main problem
    void testSetNumberOfBlocks(int n)
    {
        numberOfBlocks = n;
    }    
};

#endif /* CEB7FFC6_CAB5_4EC7_92DD_315076B1D2AC */
