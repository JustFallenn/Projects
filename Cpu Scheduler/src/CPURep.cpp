/* @Author
Student Name: Yusuf Emir Sezgin
Student ID : 150200066
Date: 26.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()    //constructor that creates a new FIFORep object for mFinishedProcess
{
    this->mFinishedProcess = new FIFORep();     
}

CPURep::~CPURep()   //destructor
{
    delete mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time) //this function is about running the Job in CPU.
{   
    if (p != NULL) {                                // if p is not NULL.
        p->setProcessTime(p->getProcessTime() - 1); //set processTime to processTime - 1.
        if (p->getProcessTime() == 0) {             //if processTime is zero than end the running in CPU  
            p->endTime = time;                      //assign p's endtime to time.
            this->getFinishedProcess()->queue(p);   //then send to the mFinishedProcess List.
            return p;
        }
    }
    return NULL;

}

FIFORep* CPURep::getFinishedProcess()   //getter for mpFinishedProcess List.
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess) //setter for mpFinishedProcess List.
{
    this->mFinishedProcess = finishedProcess;
}