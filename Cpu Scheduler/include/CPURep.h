/* @Author
Student Name: Yusuf Emir Sezgin
Student ID : 150200066
Date: 26.10.2022
*/
#ifndef _CPUREP
#define _CPUREP

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

class CPURep
{
    /*
        The CPU representation class that run  processes.
    */  
private:
    FIFORep* mFinishedProcess;
public:
    CPURep();
    ~CPURep();

    FIFORep* getFinishedProcess();
    void setFinishedProcess(FIFORep*);

    ProcessRep* runCPU(ProcessRep*, int);
};

#endif