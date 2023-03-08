![ExternalSort-blank](https://github.com/nowakkuba99/ExternalSort/actions/workflows/Release.yml/badge.svg)
<img align="right" src="https://visitor-badge.laobi.icu/badge?page_id=nowakkuba99/ExternalSort">
<h1 align="center">
<img src="https://github.com/nowakkuba99/ExternalSort/blob/main/img/externalsort.svg">
</h1>

# ExternalSort
## Brief indtroduction
This project contains of **External Sorting Algorithm** build in C++ with standard library and fstream operations.   
Also included is a big amount of [tests](https://github.com/nowakkuba99/ExternalSort/blob/main/test/tests.cc) build using **[Google Test](https://github.com/google/googletest)** framework that are integrated within [GitHub Actions](https://github.com/features/actions).


![Wikipedia](https://img.shields.io/badge/Wikipedia-%23000000.svg?style=for-the-badge&logo=wikipedia&logoColor=white)

>External sorting is a class of sorting algorithms that can handle massive amounts of data.    
>External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory, usually a disk drive - [more information](https://en.wikipedia.org/wiki/External_sorting).

## Implementation
Implemented in this project is an **External Merge Sort** model that sorts chunks that each fit in RAM, then merges the sorted chunks together.
The idea of a project is represented on a diagram below:
<h1 align="center">
<img src="https://github.com/nowakkuba99/ExternalSort/blob/main/img/diagram.svg" | height="400">
</h1>

Here the size of RAM has been ilustrated by 2, but in practice this algorithm can sort e.g. 400GB of data using PC with 8GM of RAM.
## Tests
The project uses a broad range of unit tests created in Google Test framework that have been uploaded and integrated into github actions. Incoming is a github repository template that could be used when working with google tests automation on github.
when running tests it is necessary to pass location of input test data.

```cpp
/* Inside implementation */
static std::string PATH;
/* In main test function */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  assert(argc == 2);
  PATH = argv[1];
  return RUN_ALL_TESTS();
}
```
## How to run
1. Download project
2. Run make command with attached CMakeLists.txt
3. Run ExternalSort created in build profile
>Note: Make sure to place input data in ```/resources/input.txt```

The main function runs ```solve()``` on inserted data as presented below:
```cpp
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
```
