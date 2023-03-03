/* DESCRIPTION - EXTERNAL SORT
   Since each number is an integer -> Each has the same const size of 4 bytes.
   1) Define max size of avaiable memory for data reading - BLOCK_SIZE = Avaiable_Memory [bytes] / 4
   2) Divide data into n blocks of size BLOCK_SIZE 
   3) Sort each block and save to separate file
   4) Graduatly merge files and delete leftovers
   5) Finally save sorted data into new file
*/

/* Include libraries */
#include <iostream>
/* Include user defined files */
#include "solver.hpp"

/* Main function */
int main()
{
    if(solver::solve())
    {
        std::cout<<"Problem solved - results in Sorted.txt\n";
    }
    else
    {
        std::cout<<"Problem not solved! - Error occured\n";
    }
    return 0;
}