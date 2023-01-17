/* @Author
Student Name: Yusuf Emir Sezgin
Student ID : 150200066
Date: 26.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()      //constructor that assigning to NULL.
{
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)  //constructor that assigning a ProcessRep pointer.
{
    this->mpHead = head;
    this->mpTail = this->mpHead;
}


FIFORep::~FIFORep() //destructor.
{
    delete this->mpHead;
}

void FIFORep::setHead(ProcessRep* head) //setter of ProcessRep pointer of mpHead.
{
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead() //getter of mpHead.
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail) //setter of ProcessReo pointer of mpTail.
{
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail() //getter of mpTail.
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)  //Queue function that adds to back of the FIFORep Linked List.
{
    if (this->mpHead == NULL) {     //if list is NULL, assign head and tail to p.
        this->mpHead = p;
        this->mpTail = p;
    } else {             
        this->mpTail->setNext(p);       //if list is not NULL, assign tail's next to p.
        this->mpTail = p;               //then assign tail to p.
        this->mpTail->setNext(NULL);    //lastly, assign tail's next to NULL.  
    }
}

ProcessRep* FIFORep::dequeue()                  //Deqeue function that removes from front of the FIFORep Linked List.
{   
    ProcessRep *p = NULL;                       //assign to NULL.
    if (this->mpHead == mpTail) {               //if head and tail is same. which means there is one node.
        p = this->mpHead;     
        this->mpHead = NULL;
        this->mpTail = NULL;
    } else {
        p = this->mpHead;                       //assign mpHead to p.
        this->mpHead = this->mpHead->getNext(); //assign mpHead to mpHead's next.
    }   
    return p;                                   //give p which we remove.
}

ProcessRep* FIFORep::searchID(int id)   //search for ProcessRep pointer with its id.
{   
    ProcessRep *p = this->mpHead;
    while (p->getNext() != NULL) {      //while p's (mpHead's) next is not NULL, continue.
        if (p->getProcessID() == id) {  // Is id matching with ProcessID ?
            return p;                   // if yes, then return p.
        } else {
            p = p->getNext();           // if no, then go p's next
        }
    }
    return NULL;                        //if there is no matching id then return to NULL.
}

void FIFORep::printFIFO()
{
    ProcessRep *p = this->mpHead;
    if (p == NULL) {                                                                                            //if there is no node then return.
        return;
    }
    while (p != this->mpTail) {                                                                                 //while p's (mpHead's) next is not mpTail, continue.
        cout << p->getProcessType() << p->getProcessID() << " " << p->startTime << " " << p->endTime << " ";    //print
        p = p->getNext();                                                                                       //assign p's next to p.
    }
    cout << p->getProcessType() << p->getProcessID() << " " << p->startTime << " " << p->endTime << " ";        //if p is mpTail then, print that one more time.

}