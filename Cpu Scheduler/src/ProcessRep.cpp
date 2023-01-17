/* @Author
Student Name: Yusuf Emir Sezgin
Student ID : 150200066
Date: 26.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime) // constructor that assigns variables of the node of linked list to values.
{   
    this->mpNext = NULL;
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;
    this->endTime = -1;
    this->startTime = -1;
    this->remainingTime = processTime;
    
}

ProcessRep::~ProcessRep() //destructor
{
    if (this->mpNext != NULL) {
        delete mpNext;
    }
}

ProcessRep* ProcessRep::getNext() //getter of mpNext.
{
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next) //setter of mpNext.
{
    this->mpNext = next;
}

string ProcessRep::getProcessType() //getter of mProcessType.
{
    return this->mProcessType;
}

void ProcessRep::setProcessType(string processType) //setter of mProcessType.
{
    this->mProcessType = processType;
}

int ProcessRep::getDeliverTime()  //getter of mDeliverTime.
{
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime) //setter of mDeliverTime.
{
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID() //getter of mProcessID.
{
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID) //setter of mProcessID.
{
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime() //getter of mProcessTime.
{
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime) //setter of mProcessTime.
{
    this->mProcessTime = ProcessTime;
}