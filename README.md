![ExternalSort-blank](https://github.com/nowakkuba99/ExternalSort/actions/workflows/Release.yml/badge.svg)
<img align="right" src="https://visitor-badge.laobi.icu/badge?page_id=nowakkuba99/ExternalSort">
<h1 align="center">
<img src="https://github.com/nowakkuba99/ExternalSort/blob/main/img/externalsort.svg">
</h1>

# ExternalSort
This project contains of **External Sorting Algorithm** build in C++ with standard library and fstream operations.   
Also included is a big amount of [tests](https://github.com/nowakkuba99/ExternalSort/blob/main/test/tests.cc) build using **[Google Test](https://github.com/google/googletest)** framework that are integrated within [GitHub Actions](https://github.com/features/actions).


![Wikipedia](https://img.shields.io/badge/Wikipedia-%23000000.svg?style=for-the-badge&logo=wikipedia&logoColor=white)

>External sorting is a class of sorting algorithms that can handle massive amounts of data.    
>External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory, usually a disk drive - [more information](https://en.wikipedia.org/wiki/External_sorting).

Implemented in this project is an **External Merge Sort** model that sorts chunks that each fit in RAM, then merges the sorted chunks together.
