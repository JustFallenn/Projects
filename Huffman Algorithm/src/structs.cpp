//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Yusuf Emir Sezgin
//---Student Number: 150200066
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    head = NULL;                                                        //when creating priority queue there is nothing so make head as NULL.
};
//-----------------------------------------------------//

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    Node* p = head;                                                     //point the head.

    if (newnode == NULL) {                                              //if there is no new node that needs to be added finish the function.
        return;
    }
    if (p == NULL) {                                                    //if there is no element in queue, then add the new node as head.
        head = newnode;
    } else if (newnode->token.val < p->token.val) {                     //if the newnode's token value is smaller than the head's make the new node as head.
        newnode->next = head;                                           
        head = newnode;
    } else {                                                            //if the newnode's token value is equal or smaller then head.
        Node* n = NULL;                                                 //to hold the previous node of p, create a node n. 
        while (p != NULL && (newnode->token.val >= p->token.val)) {     //while p's token value is not NULL and smaller or equal to newnode's token value
            n = p;                                                      //hold p before change.
            p = p->next;                                                //make go to p's next and make it new p then compare again with newnode.
        }
        newnode->next = p;                                              //if you find the newnode's place, place it!
        n->next = newnode;
    }
};
//-----------------------------------------------------//

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    Node* p = head;                                                     //remove from the head of priority queue
    head = p->next;                                                     
    return p;                                                           //return the front of the priority queue that you dequeued.

};
//-----------------------------------------------------//

//-------------Initialize Tree-------------//
Tree::Tree(){
    root = NULL;                                                        //when creating the tree, there is nothing so make root as NULL.
};
//-----------------------------------------------------//

//-------------Delete Tree Nodes From Memory-------------// 
Tree::~Tree(){                                                          //when program is finished delete the tree.
    deleteTree(root);                                                   //to delete tree call recursive delete funciton in destructor.
};
//-----------------------------------------------------//

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    if (node == NULL) {                                                 //if node is NULL return.
        return; 
    }
    deleteTree(node->left);                                             //go to left and check whether is NULL.
    deleteTree(node->right);                                            //go to left and cheack whether is NULL.
    delete node;                                                        //delete nodes bottom to top. 
}
//-----------------------------------------------------//

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){                       //merge nodes
   if (temp1 == NULL || temp2 == NULL) {                                //check the nodes that will be merged to not cause a problem.
       return NULL;
   }
   Node* merge = new Node();                                            //create new node to inject merged values of the given nodes.
   merge->token.val = temp1->token.val + temp2->token.val;              //sum the values and make the new merged node's value.
   merge->token.symbol = temp1->token.symbol + temp2->token.symbol;     //sum the symbols of the nodes and make the new merged node's symbol.
   
   merge->left = temp1;                                                 //make the first node as merged node's left child.
   merge->right = temp2;                                                //make the seconde node as merged node's right child.

   return merge;                                                        //return the merged node!!
};
//-----------------------------------------------------//

//-----------------------------------------------------//
void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};
//-----------------------------------------------------//