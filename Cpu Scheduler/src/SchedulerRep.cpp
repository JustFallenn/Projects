/* @Author
Student Name: Yusuf Emir Sezgin
Student ID : 150200066
Date: 26.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()    //constructor for creating mpProcessFIFOs and CPURep object pCpuobj for the Scheduler.
{
    this->mpProcessFIFO[0] = new FIFORep(); //creating the A Level of the Scheduler.
    this->mpProcessFIFO[1] = new FIFORep(); //creating the B level of the Scheduler.
    this->mpProcessFIFO[2] = new FIFORep(); //creating the C level of the Scheduler.
    this->mpRunningProcess = NULL;          //assign the running process to NULL when you create the Scheduler.
    this->pCpuObj = new CPURep();   
    this->timeSliceCount = 0;               //start the QUANTUM from zero.
    this->totalTime = 0;                    //start the TIME from zero.
}

SchedulerRep::~SchedulerRep()   //deconstructor
{
    if (mpRunningProcess == NULL) {
        delete pCpuObj;
        delete this->mpProcessFIFO[0];
        delete this->mpProcessFIFO[1];
        delete this->mpProcessFIFO[2];
    } else {
        delete mpRunningProcess;
    }
}

FIFORep* SchedulerRep::getProcessFIFO(int index)    //getter for FIFORep Lists of Scheduler.
{
    return this->mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)    //setter for FIFOREP Lists of Scheduler.
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p) //setter for current running process.
{
    if (p != NULL) {                                //if the process that we want to run on CPU is not NULL and,
        if (p->startTime == -1) {                   //if the Scheduler send the process for the first time to CPU, 
            p->startTime = this->totalTime;         //assign process's startime to current TIME.
        }
    }
    this->timeSliceCount = 0;                       //before seting process as running process on CPU, make QUANTUM to zero.
    this->mpRunningProcess = p;                     //set the running process as p.
}

ProcessRep* SchedulerRep::getRunningProcess()   //getter for current running process.
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)   //Function that adds job to a Scheduler level with 'add to back' order by looking of its processType.
{   
    if (p == NULL) {                            //if the job is NULL, then add nothing.
        return;
    }
    if (p->getProcessType() == "A") {           //if process's(job's) type is "A" then add to the A (First) level of the Scheduler.
        this->mpProcessFIFO[0]->queue(p);
        return;
    } else if (p->getProcessType() == "B") {    //if process's(job's) type is "B" then add to the B (Second) level of the Scheduler.
        this->mpProcessFIFO[1]->queue(p);
        return;
    } else if (p->getProcessType() == "C") {    //if process's(job's) type is "B" then add to the B (Third) level of the Scheduler.
        this->mpProcessFIFO[2]->queue(p);
        return;
    }
        
}

ProcessRep* SchedulerRep::popProcess()          //Function that removes the process of Scheduler with 'remove from front' order by looking if the level FIFO is empty or not.
{
    if (this->mpProcessFIFO[0]->getHead() != NULL) {            //if the first list (A Level) is not empty,
        return this->mpProcessFIFO[0]->dequeue();               //then remove from the front of the A Level.
    } else if (this->mpProcessFIFO[1]->getHead() != NULL) {     //if the first list (B Level) is not empty,
        return this->mpProcessFIFO[1]->dequeue();               //then remove from the front of the B Level.
    } else if (this->mpProcessFIFO[2]->getHead() != NULL) {     //if the first list (C Level) is not empty,
        return this->mpProcessFIFO[2]->dequeue();               //then remove from the front of the C Level.
    }
    return NULL;                                                //if the there is no process on the Scheduler return to NULL.
}

bool SchedulerRep::checkTimeSlice()                                 //Function that checks the QUANTUM is full or not for the current running process. 
{ 
    if (mpRunningProcess == NULL) {                                 //if there is no running process then QUANTUM is not full. (zero)         
        return false; 
    }

    if (mpRunningProcess->getProcessType() == "A") {                //if the running process's type is A, QUANTUM is 2.
        if (this->timeSliceCount >= 2) {                            //checks whether QUANTUM is full or not.
            return true;
        }
    } else if (mpRunningProcess->getProcessType() == "B") {         //if the running process's type is B, QUANTUM is 4.
        if (this->timeSliceCount >= 4) {                            //checks whether QUANTUM is full or not.
            return true;    
        }
    } else if (mpRunningProcess->getProcessType() == "C") {         //if the running process's type is C, QUANTUM is 8.
        if (this->timeSliceCount >= 8) {                            //checks whether QUANTUM is full or not.
            return true;            
        }
    }
    return false;                                                   //if none of the conditions is returns something, return false.
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){          //Function that just runs the process for once, and returns it.
    return this->pCpuObj->runCPU(p, totalTime);
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)  //Function which sends the job to main schedule function (Ln 119).
{   
    ProcessRep* Node = new ProcessRep(type, id, arrivalTime, processTime);          //create a new job (process) with the values that given.
    schedule(Node);                                                                 //send it to the main schedule function. 
    
}

void SchedulerRep::schedule(ProcessRep* p)                                          //the 'main' schedule function.
{                                                                                   
    //check whether there is a arriving process or not.
    if (p != NULL) {                                                                //if a arriving process is not NULL,
        this->pushProcess(p);                                                       //then push to the appopriate level of the scheduler.
    }                                                                               //if not, continue.

    //Look to the CPU, if its empty than pop a process to it.
    if (this->mpRunningProcess == NULL) {                                           //if there is no running process in the CPU,
        this->setRunningProcess(popProcess());                                      //then pop a process from the appopriate level of the scheduler, and set as running process.
    }                                                                               //if not, continue.

    //Check whether QUANTUM is full or not, if it is full, then change the running process.
    if (this->checkTimeSlice()) {                                                   //if QUANTUM is full;
        this->pushProcess(mpRunningProcess);                                        //firstly, push the current running process into the scheduler,
        this->setRunningProcess(popProcess());                                      //secondly, pop a new process form the appopriate level of scheduler, and set as running process.
    }                                                                               //if QUANTUM is zero, then continue.

    //If the arriving process is not NULL and there is a running process,
    //then check whether arriving process's Type have higher priority than the running process's.
    if (p != NULL && this->mpRunningProcess != NULL) {                              
        if (this->mpRunningProcess->getProcessType() > p->getProcessType()) {       //if p's processType have higher priority than the running process's processType;
            this->pushProcess(mpRunningProcess);                                    //firstly, push the current running process into the scheduler.
            this->setRunningProcess(popProcess());                                  //secondly, pop a new process form the appopriate level of scheduler, and set as running process.
        }                                                                           //if not, continue.
    }

    //Before running the process in CPU for one time, increase the TIME and QUANTUM.
    this->timeSliceCount++;                                                         //Increase the QUANTUM before the TIME.
    this->totalTime++;                                                              //Increase the TIME.

    //Run the sendProcessToCpu function to check whether it is returns NULL or not when it has running process as a variable.
    //If it is NULl, it means running process is finished and it needs to set new running process.
    if (sendProcessToCPU(this->mpRunningProcess) != NULL) {                         //when runs the senProcessToCpu, RunCpu works once and it decreases processTime by 1.
        this->setRunningProcess(popProcess());                                      //if processTime is zero, then return p. If sendProcessToCpu returns p, then current running process is finished
    }                                                                               //it needs to set a new running process.
                                                                                    //if processTime is not zero, then return NULl. Which means don't change the running process.
}