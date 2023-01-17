//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Yusuf Emir Sezgin
//---Student Number: 150200066
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();                                              
    //DO NOT CHANGE THIS
    char temp_symbol = sortedKey[0];                        //first symbol in the sorted string is temporary symbol.
    int counter = 0;

    for (unsigned int i = 0; i < sortedKey.size(); i++) {   //for every symbol at sorted string look for same symbols.
        if (temp_symbol == sortedKey[i]) {                  //if temp symbol eqaul to element that we currently on it in the sorted string,
            counter++;                                      //then add one to counter.
        } else {                                            //else if temp symbol is not equal to symbol that we on it then,
            Node* temp = new Node;                          //make a new node with symbol that is temp symbol, and its counter value.
            temp->token.symbol += temp_symbol;
            temp->token.val = counter;
            queue.enque(temp);                              //add to the priorty queue!!
            
            temp_symbol = sortedKey[i];                     //change the temp symbol to new symbol from sorted string.
            counter = 1;                                    //because of we are on it currently, make start counter from one.
        }
    }
    Node* temp = new Node;                                  //when the loop finished, last symbol with its value needs to be added
    temp->token.symbol += temp_symbol;                      //to the priority queue.
    temp->token.val = counter;
    queue.enque(temp);
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    findFrequency();
    while (queue.head->next != NULL) {                      //if queue's size is not 1; loop.
        Node* temp1 = queue.dequeue();                      //take the first element from head.
        Node* temp2 = queue.dequeue();                      //take the second element from head.
        queue.enque(huffmanTree.mergeNodes(temp1, temp2));  //merge first two element, then add in sorted way to queue.
    }                                                       //when there is one element that includes all element's symbols
    huffmanTree.root = queue.dequeue();                     //make that final element as root of the huffman tree.
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//----------------NEW ADDED FUNCTION!!-----------------//
//THIS FUNCTION HELPS US TO FIND BINARY VALUE OF TOKEN//
void Huffman::searchToken(Node* root, string token, string &binary, string temp) {
    if (root == NULL) {                                                                     //if a node is NULL than return.
        return;                                                                             
    } else if(root->left == NULL && root->right == NULL && root->token.symbol == token) {   //if symbol is found return the current temp as binary value of token.
        binary = temp;  
        return;
    }
    searchToken(root->left, token, binary,  temp + "0");                                    //search the symbol recursively!!
    searchToken(root->right, token, binary, temp + "1");                                    //change temp recursively,
}
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    string symbol;
    symbol += tokenChar;                                                    //convert the given char to string.
    string temp = "";                                                       //
    searchToken(traverse, symbol, tokenBinary, temp);                       //search for binary value of token when found change the tokenBinary as that value
    return tokenBinary;                                                     //return the tokenBinary.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    encodedBinaryPassword = "";
    encodedValPassword  = "";
    for (unsigned int i = 0; i < password.size(); i++) {                                        //look the symbols one by one of the given password.
        char pass_symbol = password[i];                                                         //
        string encoded;                                                                         //make the symbol's binary value as encoded!
        string binary_token_value = getTokenBinary(pass_symbol, huffmanTree.root, encoded);     //to use binary value.
        encodedBinaryPassword += binary_token_value;                                            //add binary value of the symbol to the binary password.
        encodedValPassword += to_string(binary_token_value.size());                             //assume encoded is 101011 than valule password will be "6" for one symbol!
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){      
    decodedPassword = "";
    for (unsigned int i = 0; i < encodedValPassword.size(); i++) {                   //divide given binary password by the value's of the value password one by one!
        int value = int(encodedValPassword[i] - '0');                                //convert the depth value of a symbol from string to int.
        string encoded_token = encodedBinaryPassword.substr(0, value);               //find the binary value with given depth by taking the according part from binary password.
        encodedBinaryPassword.erase(0, value);                                       //to find another symbol when look for it erase the old binary value from the start of binary password.
        decodeToken(encoded_token);                                                  //function that finds the symbol according to binary value that we found, and adds to decoded password.
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    Node* p = huffmanTree.root;                                           //point the root of the huffman tree.
    for (unsigned int i = 0; i < encodedToken.size(); i++) {              //find the symbol with given it's binary value.
        if (encodedToken[i] == '1') {                                     //if encounter '1' go to right.
            p = p->right;
        } else if (encodedToken[i] == '0') {                              //if encounter '0' go to left.
            p = p->left;    
        }   
    }                                                                     //when you finished and arrived a node.
    decodedPassword += p->token.symbol;                                   //that node's token is what do we want to find add it to decodedp password.
};
//-----------------------------------------------------//




//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};
//-----------------------------------------------------//