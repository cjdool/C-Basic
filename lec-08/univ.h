//
//  univ.h
//  univlist
//
//  Created by 장주현 on 2/22/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#ifndef univ_h
#define univ_h
#include "Node.h"
#include <string>
#include <vector>
#include <iostream>

/*unvlist is double linked list of Node with operation overloading*/
/*unvlist sequential access only*/
template<typename A>
class unvlist {
public:
    /*Constructor and desconstructor*/
    unvlist(); // create an empty doubly linked list
    unvlist(const A* arr, int array_length); // creates a list with elements in array arr
    ~unvlist(); // free the allocated list
    
    /*Opeartion Overloading*/
    unvlist operator+ (const unvlist &Obj); // concatenates the two given list A and B
    bool operator== (const unvlist &Obj); // check whether list A and B have same elements or not
    
    /*Function Template Functioning*/
    void set(int n, const A &val); // updates the element of index n with the value val
    A get(int n); // returns the elements of index n
    void insert (int n, const A &val); // inserts and returns val at the index n of the list
    void erase (int n); // removes and returns the element at the index n of the list
    int size(void); // returns the length of the list
    
    /*Queue Manage Method*/
    A pop_back (void);// removes the last element of the list
    A pop_front (void);// removes the first element of the list
    void push_back (const A &val);// inserts the value at the end of the list
    void push_front (const A &val);// inserts the value val at the beginning of the list
    
private:
    int numnode;
    Node<A> *nodeaddr;
};

class UnivEX // can not check Out of Range in Dynamic Array -> C++ is undefined behavior
{
private:
    int ErrorType;
    std::pair<std::string, std::string> callback;
    void Errornsol (void)
    {
        switch (ErrorType) {
            case 0:
                callback = std::make_pair("array_length is not positive", "length must be positive value");
                break;
            case 1:
                callback = std::make_pair("Index is negative", "Index must be non-negative value");
                break;
            case 2:
                callback = std::make_pair("Index is out of Range", "Index number is over total count of node");
                break;
            default:
                callback = std::make_pair("Undefined Error", "Undefined Error");
                break;
        }
    }
public:
    UnivEX(int type)
    {
        ErrorType = type;
        Errornsol();
    }
    void What()
    {
        std::cout << "Error: " << callback.first << std::endl << "Detail: " << callback.second << std::endl;
    }
};



#endif /* univ_h */
