/* Includes */
#include <gtest/gtest.h>
/* User includes */
#include "../src/fileReader.cpp"
#include "../src/fileWriter.cpp"
#include "../src/solver.cpp"

/* 
--------------------------------------------------------------
Test fileReader class 
--------------------------------------------------------------
*/
// Check reading one int
TEST(FileReaderTests, ReadDataInt)
{
  //Create file reader object
  fileReader inputFile("/tests/someData.txt");
  int x;
  auto status = inputFile.readToInt(x);
  EXPECT_EQ(x,10);  //Data read
  EXPECT_EQ(status,true); //No error
}
// Check reading int's when the file is empty
TEST(FileReaderTests, ReadNoDataInt)
{
  //Create file reader object
  fileReader inputFile("/tests/noData.txt");
  int x = 5;
  auto status = inputFile.readToInt(x);
  EXPECT_EQ(x,5); //Expected no value changed
  EXPECT_EQ(status,false);  //Error reported
}
TEST(FileReaderTests, DataEndedWhileReading)
{
  //Create file reader object
  fileReader inputFile("/tests/someData.txt");
  int x;
  auto status = inputFile.readToInt(x);
  EXPECT_EQ(x,10);  //Data read
  EXPECT_EQ(status,true); //No error
  status = inputFile.readToInt(x);
  EXPECT_EQ(x,20);  //Data read
  EXPECT_EQ(status,true); //No error
  status = inputFile.readToInt(x);
  EXPECT_EQ(x,25);  //Data read
  EXPECT_EQ(status,true); //No error
  status = inputFile.readToInt(x);
  EXPECT_EQ(x,25);  //Data not read
  EXPECT_EQ(status,false); //Error
}
// Check reading to vector when there is more data than block size asked to read
TEST(FileReaderTests,ReadDataToVectorAllDataFit)
{
  //Create file reader object
  fileReader inputFile("/tests/someData.txt");
  std::vector<int> x;
  auto status = inputFile.readToVector(x,2);
  EXPECT_EQ(x[0],10);  //Data read
  EXPECT_EQ(x[1],20);  //Data read
  EXPECT_EQ(x.size(),2);  //Correct size
  EXPECT_EQ(status,true); //No error
}
// Check reading to vector when there is less data than block size asked to read
TEST(FileReaderTests,ReadDataToVectorRequestToBig)
{
  //Create file reader object
  fileReader inputFile("/tests/someData.txt");
  std::vector<int> x;
  auto status = inputFile.readToVector(x,10);
  EXPECT_EQ(x[0],10);  //Data read
  EXPECT_EQ(x[1],20);  //Data read
  EXPECT_EQ(x[2],25);  //Data read
  EXPECT_EQ(x.size(),3);  //Correct size
  EXPECT_EQ(status,true); //No error
}
// Check reading to vector when data has ended
TEST(FileReaderTests,ReadDataToVectorDataEnded)
{
  //Create file reader object
  fileReader inputFile("/tests/someData.txt");
  std::vector<int> x;
  auto status = inputFile.readToVector(x,2);
  EXPECT_EQ(x[0],10);  //Data read
  EXPECT_EQ(x[1],20);  //Data read
  EXPECT_EQ(status,true); //No error
  EXPECT_EQ(x.size(),2);  //Correct size
  status = inputFile.readToVector(x,2);
  EXPECT_EQ(x[2],25);  //Data read
  EXPECT_EQ(x.size(),3);  //Correct size
  EXPECT_EQ(status,true); //No error
  status = inputFile.readToVector(x,2);
  EXPECT_EQ(x.size(),3);  //Correct size
  EXPECT_EQ(status,false); //Read error
}
// Check reading to vector when file empty
TEST(FileReaderTests,ReadDataToVectorNoData)
{
  //Create file reader object
  fileReader inputFile("/tests/noData.txt");
  std::vector<int> x;
  auto status = inputFile.readToVector(x,2);
  EXPECT_EQ(x.size(),0);  //Correct size
  EXPECT_EQ(status,false); //Read error
}
/* 
--------------------------------------------------------------
Test fileWriter class 
--------------------------------------------------------------
*/
struct FileWriterTests : public ::testing::Test
{
  fileWriter outputFile;  //Output file
  fileReader inputFile;  //Input file
  void SetUp() override
  {
    outputFile.openFile("/tests/output/output.txt",fileActions::OVERWRITE);  //Open file
  }

  void TearDown() override
  {
    outputFile.closeFile();   //Close file if not closed
    outputFile.removeFile();  //Remove file
  }
};

// Check writing from vector
TEST_F(FileWriterTests,WriteFromVector)
{
  std::vector<int> testVec, inputVec;
  testVec.push_back(10);
  testVec.push_back(15);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  inputFile.openFile("/tests/output/output.txt");
  auto status = inputFile.readToVector(inputVec,10);
  EXPECT_EQ(inputVec.size(),2);  //Correct size
  EXPECT_EQ(inputVec[0],10);
  EXPECT_EQ(inputVec[1],15);
  EXPECT_EQ(status,true); //Read
}
// Check appending int to file
TEST_F(FileWriterTests,AppendIntToFile)
{
  std::vector<int> testVec, inputVec;
  testVec.push_back(10);
  testVec.push_back(15);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  inputFile.openFile("/tests/output/output.txt");
  auto status = inputFile.readToVector(inputVec,10);
  EXPECT_EQ(inputVec.size(),2);  //Correct size
  EXPECT_EQ(inputVec[0],10);
  EXPECT_EQ(inputVec[1],15);
  EXPECT_EQ(status,true);
  /* Append value to file */
  inputVec.clear();
  outputFile.openFile("/tests/output/output.txt",fileActions::APPEND);
  int x = 10;
  outputFile.appendValueToFile(&x);
  outputFile.closeFile();
  inputFile.openFile("/tests/output/output.txt");
  status = inputFile.readToVector(inputVec,10);
  EXPECT_EQ(inputVec.size(),3);  //Correct size
  EXPECT_EQ(inputVec[0],10);
  EXPECT_EQ(inputVec[1],15);
  EXPECT_EQ(inputVec[2],10);
  EXPECT_EQ(status,true); //Read
}
// Try appending when wrong mode
TEST_F(FileWriterTests,AppendWrongMode)
{
  std::vector<int> testVec, inputVec;
  testVec.push_back(10);
  testVec.push_back(15);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  inputFile.openFile("/tests/output/output.txt");
  auto status = inputFile.readToVector(inputVec,10);
  EXPECT_EQ(inputVec.size(),2);  //Correct size
  EXPECT_EQ(inputVec[0],10);
  EXPECT_EQ(inputVec[1],15);
  EXPECT_EQ(status,true);
  /* Append value to file */
  inputVec.clear();
  outputFile.openFile("/tests/output/output.txt",fileActions::OVERWRITE);
  int x = 10;
  status = outputFile.appendValueToFile(&x);
  EXPECT_EQ(status,false);  //Check if appending not done
}
/* 
--------------------------------------------------------------
Test solver elements 
--------------------------------------------------------------
*/
//Check behaviour of divide for empty file
TEST(SolverTests,DivideAndSort_emptyFile)
{
  solver solveObj("/tests/noData.txt");
  auto status = solveObj.sortIntoInitialPartitions(); //Try sorting
  EXPECT_EQ(status,false);
}
//Check behaviour of divide for number of int = (2n)*BLOCK_SIZE
TEST(SolverTests,DivideAndSort_2n)
{
  // BLOCK_SIZE = 2 -> 4 int's inside file
  fileReader inputFileA;  //Input file
  fileReader inputFileB;  //Input file
  solver solveObj("/tests/input2n.txt");
  auto status = solveObj.sortIntoInitialPartitions();
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  inputFileB.openFile("Block1.txt");
  std::vector<int> A,B;
  inputFileA.readToVector(A,10);  //Read and check if sorted properly
  inputFileB.readToVector(B,10);
  ASSERT_EQ(A.size(),2);
  EXPECT_EQ(A[0],10);
  EXPECT_EQ(A[1],20);
  ASSERT_EQ(B.size(),2);
  EXPECT_EQ(B[0],25);
  EXPECT_EQ(B[1],30);
  inputFileA.closeFile(); //Delete files
  inputFileB.closeFile();
  inputFileA.removeFile();
  inputFileB.removeFile();
}
//Check behaviour of divide for number of int = (2n+1)*BLOCK_SIZE
TEST(SolverTests,DivideAndSort_2n1)
{
  // BLOCK_SIZE = 2 -> 5 int's inside file
  fileReader inputFileA;  //Input file
  fileReader inputFileB;  //Input file
  fileReader inputFileC;  //Input file
  solver solveObj("/tests/input2n_1.txt");
  auto status = solveObj.sortIntoInitialPartitions(); //Divide and sort
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  inputFileB.openFile("Block1.txt");
  inputFileC.openFile("Block2.txt");
  std::vector<int> A,B,C;
  inputFileA.readToVector(A,10);    //Check if sorted properly
  inputFileB.readToVector(B,10);
  inputFileC.readToVector(C,10);
  ASSERT_EQ(A.size(),2);
  EXPECT_EQ(A[0],10);
  EXPECT_EQ(A[1],20);
  ASSERT_EQ(B.size(),2);
  EXPECT_EQ(B[0],25);
  EXPECT_EQ(B[1],30);
  ASSERT_EQ(C.size(),1);
  EXPECT_EQ(C[0],4);
  inputFileA.closeFile(); //Delete leftover files
  inputFileB.closeFile();
  inputFileC.closeFile();
  inputFileA.removeFile();
  inputFileB.removeFile();
  inputFileC.removeFile();
}
//Check behaviour of divide for already sorted
TEST(SolverTests,DivideAndSort_AlreadySorted)
{
  // BLOCK_SIZE = 2 -> 6 int's inside file
  fileReader inputFileA;  //Input file
  fileReader inputFileB;  //Input file
  fileReader inputFileC;  //Input file
  solver solveObj("/tests/inputSorted.txt");
  auto status = solveObj.sortIntoInitialPartitions(); //Divide and sort
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  inputFileB.openFile("Block1.txt");
  inputFileC.openFile("Block2.txt");
  std::vector<int> A,B,C;
  inputFileA.readToVector(A,10);
  inputFileB.readToVector(B,10);
  inputFileC.readToVector(C,10);
  ASSERT_EQ(A.size(),2);    //Check if sorted properly
  EXPECT_EQ(A[0],1);
  EXPECT_EQ(A[1],2);
  ASSERT_EQ(B.size(),2);
  EXPECT_EQ(B[0],34);
  EXPECT_EQ(B[1],50);
  ASSERT_EQ(C.size(),2);
  EXPECT_EQ(C[0],20);
  EXPECT_EQ(C[1],69);
  inputFileA.closeFile();   //Delete files
  inputFileB.closeFile();
  inputFileC.closeFile();
  inputFileA.removeFile();
  inputFileB.removeFile();
  inputFileC.removeFile();
}
//Check behaviour of divide for already sorted nonascending order
TEST(SolverTests,DivideAndSort_AlreadySortedNonAscending)
{
  // BLOCK_SIZE = 2 -> 6 int's inside file
  fileReader inputFileA;  //Input file
  fileReader inputFileB;  //Input file
  fileReader inputFileC;  //Input file
  solver solveObj("/tests/inputSortedNonAscending.txt");
  auto status = solveObj.sortIntoInitialPartitions(); //Divide and sort
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  inputFileB.openFile("Block1.txt");
  inputFileC.openFile("Block2.txt");
  std::vector<int> A,B,C;
  inputFileA.readToVector(A,10);
  inputFileB.readToVector(B,10);
  inputFileC.readToVector(C,10);
  ASSERT_EQ(A.size(),2);    //Check proper sorting
  EXPECT_EQ(A[0],20);
  EXPECT_EQ(A[1],69);
  ASSERT_EQ(B.size(),2);
  EXPECT_EQ(B[0],34);
  EXPECT_EQ(B[1],50);
  ASSERT_EQ(C.size(),2);
  EXPECT_EQ(C[0],1);
  EXPECT_EQ(C[1],2);
  inputFileA.closeFile();   //Delete files
  inputFileB.closeFile();
  inputFileC.closeFile();
  inputFileA.removeFile();
  inputFileB.removeFile();
  inputFileC.removeFile();
}
//Check merging 2 blocks of size BLOCKSIZE into 1
TEST(SolverTests,Merge2Blocks_BLOCKSIZE)
{
  /* Preparation - create 2 files */
  fileReader inputFileA;  //Input file
  fileReader inputFileB;  //Input file
  solver solveObj("/tests/input2n.txt");
  auto status = solveObj.sortIntoInitialPartitions();
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  inputFileB.openFile("Block1.txt");
  std::vector<int> A,B;
  inputFileA.readToVector(A,10);
  inputFileB.readToVector(B,10);
  ASSERT_EQ(A.size(),2);
  EXPECT_EQ(A[0],10);
  EXPECT_EQ(A[1],20);
  ASSERT_EQ(B.size(),2);
  EXPECT_EQ(B[0],25);
  EXPECT_EQ(B[1],30);
  inputFileA.closeFile();
  inputFileB.closeFile();
  /* Merge files */
  status = solveObj.mergeSortedBlocks();
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  A.clear();
  inputFileA.readToVector(A,10);
  ASSERT_EQ(A.size(),4);
  EXPECT_EQ(A[0],10);
  EXPECT_EQ(A[1],20);
  EXPECT_EQ(A[2],25);
  EXPECT_EQ(A[3],30);
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Check merging 3 blocks of size BLOCKSIZE into 1
TEST(SolverTests,Merge3Blocks_BLOCKSIZE)
{
  /* Preparation */
  fileReader inputFileA;  //Input file
  fileReader inputFileB;  //Input file
  fileReader inputFileC;  //Input file
  solver solveObj("/tests/inputSortedNonAscending.txt");
  auto status = solveObj.sortIntoInitialPartitions();
  EXPECT_EQ(status,true);
  /* Merge files */
  status = solveObj.mergeSortedBlocks();
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,10);
  ASSERT_EQ(A.size(),6);
  EXPECT_EQ(A[0],1);
  EXPECT_EQ(A[1],2);
  EXPECT_EQ(A[2],20);
  EXPECT_EQ(A[3],34);
  EXPECT_EQ(A[4],50);
  EXPECT_EQ(A[5],69);
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Check merging 2 blocks of size 5*BLOCKSIZE
TEST(SolverTests,Merge2Blocks_10xBLOCKSIZE)
{
  /* Preparation */
  fileWriter outputFile;
  outputFile.openFile("Block0.txt",fileActions::OVERWRITE);
  std::vector<int> testVec;
  testVec.push_back(2);
  testVec.push_back(10);
  testVec.push_back(15);
  testVec.push_back(48);
  testVec.push_back(60);
  testVec.push_back(61);
  testVec.push_back(70);
  testVec.push_back(74);
  testVec.push_back(80);
  testVec.push_back(90);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  outputFile.openFile("Block1.txt",fileActions::OVERWRITE);
  testVec.clear();
  testVec.push_back(1);
  testVec.push_back(30);
  testVec.push_back(47);
  testVec.push_back(51);
  testVec.push_back(62);
  testVec.push_back(66);
  testVec.push_back(79);
  testVec.push_back(81);
  testVec.push_back(99);
  testVec.push_back(100);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  /* Merge files */
  fileReader inputFileA;  //Input file
  solver solveObj("/tests/inputSortedNonAscending.txt");
  solveObj.testSetNumberOfBlocks(2);
  auto status = solveObj.mergeSortedBlocks();
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,100); //check if correct size
  ASSERT_EQ(A.size(),20); 
  int max = 0;
  for(auto const& val:A)  //Check if sorted
  {
    EXPECT_GE(val,max);
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Check merging 2 blocks of size 5*BLOCKSIZE + some data
TEST(SolverTests,Merge2Blocks_10xBLOCKSIZE_andSomeData)
{
  /* Preparation */
    /* Preparation */
  fileWriter outputFile;
  outputFile.openFile("Block0.txt",fileActions::OVERWRITE);
  std::vector<int> testVec;
  testVec.push_back(2);
  testVec.push_back(10);
  testVec.push_back(15);
  testVec.push_back(48);
  testVec.push_back(60);
  testVec.push_back(61);
  testVec.push_back(70);
  testVec.push_back(74);
  testVec.push_back(80);
  testVec.push_back(90);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  outputFile.openFile("Block1.txt",fileActions::OVERWRITE);
  testVec.clear();
  testVec.push_back(1);
  testVec.push_back(30);
  testVec.push_back(47);
  testVec.push_back(51);
  testVec.push_back(62);
  testVec.push_back(66);
  testVec.push_back(79);
  testVec.push_back(81);
  testVec.push_back(99);
  testVec.push_back(100);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  outputFile.openFile("Block2.txt",fileActions::OVERWRITE);
  testVec.clear();
  testVec.push_back(9);
  testVec.push_back(26);
  testVec.push_back(49);
  testVec.push_back(98);
  outputFile.writeFromVector(testVec);
  outputFile.closeFile();
  /* Merge files */
  fileReader inputFileA;  //Input file
  solver solveObj("/tests/inputSortedNonAscending.txt");
  solveObj.testSetNumberOfBlocks(3);
  auto status = solveObj.mergeSortedBlocks();   
  EXPECT_EQ(status,true);
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,100); //Check if correct size
  ASSERT_EQ(A.size(),24);
  int max = 0;
  for(auto const& val:A)    //Check if sorted properly
  {
    EXPECT_GE(val,max);
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
/*
--------------------------------------------------------------
Check solving whole problem
--------------------------------------------------------------
*/
//Input file size == BLOCKSIZE
TEST(AppTests,InputEqualBLOCKSIZE)
{
  /* Solve */
  solver solverObj("/tests/input2n.txt");
  auto status = solverObj.sortIntoInitialPartitions();  //Divide and sort
  EXPECT_EQ(status,true);
  status = solverObj.mergeSortedBlocks();    //Merge
  EXPECT_EQ(status,true);
  fileReader inputFileA;  //Input file
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,100);
  ASSERT_EQ(A.size(),4);  //Check proper size
  int max = 0;
  for(auto const& val:A)  //Check if sorted properly
  {
    EXPECT_GE(val,max);
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Input file size == 10*BLOCKSIZE random
TEST(AppTests,Input_10x_BLOCKSIZE)
{
  solver solverObj("/tests/input10BLOCK_SIZE.txt");
  auto status = solverObj.sortIntoInitialPartitions();  //Divide and sort
  EXPECT_EQ(status,true);
  status = solverObj.mergeSortedBlocks();    //Merge
  EXPECT_EQ(status,true);
  fileReader inputFileA;  //Input file
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,100);
  ASSERT_EQ(A.size(),20);   //Check correct size
  int max = 0;
  for(auto const& val:A)
  {
    EXPECT_GE(val,max);   //Check if sorted
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Input file size == 10*BLOCKSIZE sorted ascending
TEST(AppTests,Input_10x_BLOCKSIZE_ascending)
{
  solver solverObj("/tests/input10BLOCK_SIZE_Sorted.txt");
  auto status = solverObj.sortIntoInitialPartitions();  //Divide and sort
  EXPECT_EQ(status,true);
  status = solverObj.mergeSortedBlocks();    //Merge
  EXPECT_EQ(status,true);
  fileReader inputFileA;  //Input file
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,100);
  ASSERT_EQ(A.size(),20);   //Check correct size
  int max = 0;
  for(auto const& val:A)
  {
    EXPECT_GE(val,max);   //Check if sorted
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Input file size == 10*BLOCKSIZE sorted nonascending
TEST(AppTests,Input_10x_BLOCKSIZE_nonascending)
{
  solver solverObj("/tests/input10BLOCK_SIZE_SoretdDescending.txt");
  auto status = solverObj.sortIntoInitialPartitions();  //Divide and sort
  EXPECT_EQ(status,true);
  status = solverObj.mergeSortedBlocks();    //Merge
  EXPECT_EQ(status,true);
  fileReader inputFileA;  //Input file
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,100);
  ASSERT_EQ(A.size(),20);   //Check size
  int max = 0;
  for(auto const& val:A)
  {
    EXPECT_GE(val,max);   //Check if sorted
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}
//Input file size == 9999 ints -> random
TEST(AppTests,Input_9999)
{
  solver solverObj("/tests/input_9999.txt");
  auto status = solverObj.sortIntoInitialPartitions();  //Divide and sort
  EXPECT_EQ(status,true);
  status = solverObj.mergeSortedBlocks();    //Merge
  EXPECT_EQ(status,true);
  fileReader inputFileA;  //Input file
  inputFileA.openFile("Block0.txt");
  std::vector<int> A;
  inputFileA.readToVector(A,10000);
  ASSERT_EQ(A.size(),9999);   //Check if correct size
  int max = 0;
  for(auto const& val:A)
  {
    EXPECT_GE(val,max);   //Check if sorted
    max = val;
  }
  /* Delete files */
  inputFileA.closeFile();
  inputFileA.removeFile();
}

