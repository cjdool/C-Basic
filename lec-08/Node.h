//
//  Node.h
//  univlist
//
//  Created by 장주현 on 2/22/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <string>

/*Node using template*/
/*Node support 9types -> bool, int, char, short, long, longlong, float, double, string*/
template<typename T>
class Node
{
private:
    Node *head;
    Node *tail;
    T data;
public:
    Node()
    {
        head = nullptr;
        tail = nullptr;
    }
    void Clear (void)
    {
        delete tail;
        tail = nullptr;
    }
    void NewTail (void)
    {
        tail = new Node;
        tail->AdjustHead(this);
    }
    void AdjustHead (Node *ptr)
    {
        head = ptr;
    }
    void AdjustTail (Node *ptr)
    {
        tail = ptr;
    }
    void Setdata (T input)
    {
        data = input;
    }
    Node* getHead (void)
    {
        return head;
    }
    Node* getTail (void)
    {
        return tail;
    }
    T Getdata (void)
    {
        return data;
    }
};

#endif /* Node_h */
