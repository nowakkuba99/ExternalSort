/* Includes */

/* User includes */
#include "solver.hpp"

solver::solver(const std::string inputFileName)
{
    inputFileA.openFile(inputFileName);  //Open input file
}

/* 
 Function used to divide input data into partitions of size max avaiable memory
 and sort each partition in separate file.
 Parameters: -
 Returns: Status OK/ERROR
 */
bool solver::sortIntoInitialPartitions()
{
    bool status = errorReportBlock.OK;  //Set default value as OK
    while(true)
    {
        std::vector<int> tempDataStorage;   //Vector to store current block of values
        status = inputFileA.readToVector(tempDataStorage,BLOCK_SIZE); //Read block of data of fixed size
        if(status == errorReportBlock.OK)   //If some data was read
        {
            std::sort(tempDataStorage.begin(),tempDataStorage.end());   //Sort the data
            status = outputFile.openFile((const std::string)("Block"+std::to_string(blockCounter)+".txt"),fileActions::OVERWRITE);  //Open file to save as output
            if(status == errorReportBlock.ERROR)
            {
                return errorReportBlock.ERROR;
            }
            status = outputFile.writeFromVector(tempDataStorage);   //Write sorted data to new file of the BLOCK_SIZE
            if(status == errorReportBlock.ERROR)
            {
                return errorReportBlock.ERROR;
            }
            blockCounter++; //Increase block counter
        }
        else    //If no data read -> EOF -> break the loop
        {
            break;
        }
    }
    outputFile.closeFile();    //Close output file
    numberOfBlocks = blockCounter;  //Assign current number of blocks to variable
    if(blockCounter>0)
        return errorReportBlock.OK;
    else
        return errorReportBlock.ERROR;  //If no blocks read -> Report error
}
/*
 Function to merge created sorted partitions to one file.
 Reading max 1 value at the time from input files
 */
bool solver::mergeSortedBlocks()
{
    bool blockAOpen = false, blockBOpen=false;
    int blockAValue, blockBValue;
    blockCounter = 0;   //Reset block counter
    int blockCounterSave = 0;
    while(numberOfBlocks>1) //While there is more than 1 block
    {
        blockCounterSave = 0;   //Reset blockcounter save
        for(int i = 0; i<numberOfBlocks; i+=2)
        {
            blockCounter = i;   //Set blockCounter to read
            //Set input files
            inputFileA.openFile((const std::string)("Block" + std::to_string(blockCounter) + ".txt"));
            inputFileB.openFile((const std::string)("Block" + std::to_string(blockCounter+1) + ".txt"));
            //Try reading value
            blockAOpen = inputFileA.readToInt(blockAValue);
            blockBOpen = inputFileB.readToInt(blockBValue);
            //Judge current state
            if(blockAOpen == errorReportBlock.OK && blockBOpen != errorReportBlock.OK)   //If block A open and B fail
            {
                if(blockCounter == 0)
                {
                    //End of algorithm
                    numberOfBlocks = 1;
                }
                else
                {
                    inputFileA.closeFile();
                    inputFileA.renameFile("Block" + std::to_string(blockCounterSave) + ".txt");
                    blockCounterSave++;
                }
            }
            else if(blockAOpen != errorReportBlock.OK && blockBOpen != errorReportBlock.OK)
            {
                //Error opening both blocks
            }
            else    //Both blocks opened correctly
            {
                outputFile.openFile((const std::string)("Temp" + std::to_string(blockCounterSave)+".txt"),fileActions::APPEND);
                while(blockAOpen == errorReportBlock.OK && blockBOpen == errorReportBlock.OK) //If both blocks have values in them
                {
                    if(blockAValue < blockBValue)
                    {
                        outputFile.appendValueToFile(&blockAValue); //Append smaller one
                        blockAOpen = inputFileA.readToInt(blockAValue); //Read next one
                    }
                    else
                    {
                        outputFile.appendValueToFile(&blockBValue); //Append smaller one
                        blockBOpen = inputFileB.readToInt(blockBValue); //Read next one
                    }
                }
                // At this point one of blocks is empty
                if(blockAOpen != errorReportBlock.OK)   //If blockA empty -> append rest of B to output
                {
                    outputFile.appendValueToFile(&blockBValue); //Append current buffer
                    while(true)
                    {
                        std::vector<int> tempDataStorage;   //Vector to store current block of values
                        blockBOpen = inputFileB.readToVector(tempDataStorage,BLOCK_SIZE);     //Read block of data of max fixed size
                        if(blockBOpen == errorReportBlock.OK)
                        {
                            outputFile.writeFromVector(tempDataStorage);
                        }
                        else    //No data read
                        {
                            break;  
                        }
                    }
                }
                else
                {
                    outputFile.appendValueToFile(&blockAValue);   //Append current buffor
                    while(true)
                    {
                        std::vector<int> tempDataStorage;   //Vector to store current block of values
                        blockAOpen = inputFileA.readToVector(tempDataStorage,BLOCK_SIZE);     //Read block of data of max fixed size
                        if(blockAOpen == errorReportBlock.OK)
                        {
                            outputFile.writeFromVector(tempDataStorage);
                        }
                        else    //No data read
                        {
                            break;  
                        }
                    }
                }
                inputFileA.closeFile();     //Close and delete input files
                inputFileB.closeFile();
                inputFileA.removeFile();
                inputFileB.removeFile();
                outputFile.closeFile();     //Close and rename output file
                outputFile.renameFile("Block" + std::to_string(blockCounterSave)+".txt");
                blockCounterSave++;     //Increment numer of new blocks
            }
        }
        numberOfBlocks = blockCounterSave;  //Update total number of blocks
    }

    return true;
}

bool solver::solve()
{
    solver solverObject("input.txt");      //Create solver object
    if(solverObject.sortIntoInitialPartitions() == true)  //Divide and sort
    {
        if(solverObject.mergeSortedBlocks() == true)    //Merge
        {
            solverObject.outputFile.openFile("Block0.txt",fileActions::APPEND);   //Rename final output file
            solverObject.outputFile.closeFile();
            solverObject.outputFile.renameFile("Sorted.txt");
            return true;
        }
        else
            return false;
    }
    #ifdef DEBUG
    errorReportBlock.showError(errorReportBlock.SOLVER_ERROR);
    #endif
    return false;
}