//
//  univ.cpp
//  univlist
//
//  Created by 장주현 on 2/22/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include "univ.h"

template <typename A>
unvlist<A>::unvlist()
{
    numnode = 0;
    nodeaddr = nullptr;
}

template <typename A>
unvlist<A>::unvlist(const A* arr, int array_length)
{
    try {
        if (array_length > 0)
        {
            numnode = array_length;
            nodeaddr = new Node<A>;
            Node<A> *currentptr = nodeaddr;
            int i = 0;
            while (currentptr != nullptr)
            {
                currentptr->Setdata(arr[i]);
                if (i != numnode - 1) // check it is last node?
                {
                    currentptr->NewTail();
                }
                currentptr = currentptr->getTail();
                i++;
            }
        }
        else
        {
            throw UnivEX(0);
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
}

template <typename A>
unvlist<A>::~unvlist()
{
    if (numnode != 0)
    {
        /*Search Last Node*/
        Node<A> *currentptr = nodeaddr;
        while (currentptr->getTail() != nullptr)
        {
            currentptr = currentptr->getTail();
        }
        /*delete process*/
        currentptr = currentptr->getHead();
        while (currentptr != nullptr)
        {
            currentptr->Clear();
            currentptr = currentptr->getHead();
        }
        delete nodeaddr;
    }
}

template <typename A>
void unvlist<A>::set(int n, const A &val)
{
    try {
        if (n < 0)
        {
            throw UnivEX(1);
        }
        else
        {
            if (n < numnode)
            {
                Node<A> *currentptr = nodeaddr;
                for (int i = 0; i < n; i++)
                {
                    currentptr = currentptr->getTail();
                }
                currentptr->Setdata(val);
            }
            else
            {
                throw UnivEX(2);
            }
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
}

template <typename A>
A unvlist<A>::get(int n)
{
    A retval;
    try {
        if (n < 0)
        {
            throw UnivEX(1);
        }
        else
        {
            if (n < numnode)
            {
                Node<A> *currentptr = nodeaddr;
                for (int i = 0; i < n; i++)
                {
                    currentptr = currentptr->getTail();
                }
                retval = currentptr->Getdata();
            }
            else
            {
                throw UnivEX(2);
            }
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
    return retval;
}

template <typename A>
void unvlist<A>::insert(int n, const A &val)
{
    try {
        if (n < 0)
        {
            throw UnivEX(1);
        }
        else
        {
            if (n == 0)
            {
                this->push_front(val);
            }
            else if (n < numnode)
            {
                numnode++;
                /*Find out n-1 th node*/
                Node<A> *currentptr = nodeaddr;
                Node<A> *futureptr = nullptr;
                for (int i = 0; i < n-1; i++)
                {
                    currentptr = currentptr->getTail();
                }
                futureptr = currentptr->getTail();
                /*Make New node and adjust Node head and tail*/
                currentptr->AdjustTail(nullptr);
                currentptr->NewTail();
                currentptr = currentptr->getTail();
                currentptr->Setdata(val);
                currentptr->AdjustTail(futureptr);
                futureptr->AdjustHead(currentptr);
            }
            else if (n == numnode)
            {
                this->push_back(val);
            }
            else
            {
                throw UnivEX(2);
            }
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
}

template <typename A>
void unvlist<A>::erase(int n)
{
    try {
        if (n < 0)
        {
            throw UnivEX(1);
        }
        else
        {
            if (n == 0)
            {
                this->pop_front();
            }
            else if (n < numnode - 1)
            {
                numnode--;
                /*Find out n-1 th node*/
                Node<A> *currentptr = nodeaddr;
                Node<A> *midptr = nullptr;
                Node<A> *futureptr = nullptr;
                for (int i = 0; i < n-1; i++)
                {
                    currentptr = currentptr->getTail();
                }
                midptr = currentptr->getTail(); // find out n th node
                futureptr = midptr->getTail(); // find out n+1 th node
                /*Delete New node and adjust Node head and tail*/
                midptr->AdjustTail(nullptr);
                futureptr->AdjustHead(currentptr);
                currentptr->Clear();
                currentptr->AdjustTail(futureptr);
            }
            else if (n == numnode -1)
            {
                this->pop_back();
            }
            else
            {
                throw UnivEX(2);
            }
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
}

template <typename A>
int unvlist<A>::size(void)
{
    return numnode;
}

template <typename A>
A unvlist<A>::pop_back(void)
{
    try {
        if (numnode != 0)
        {
            /*Search last node*/
            numnode--;
            Node<A> *currentptr = nodeaddr;
            while (currentptr->getTail() != nullptr)
            {
                currentptr = currentptr->getTail();
            }
            A retval = currentptr->Getdata();
            if (numnode != 0)
            {
                currentptr = currentptr->getHead();
                currentptr->Clear();
            }
            else
            {
                delete nodeaddr;
                nodeaddr = nullptr;
            }
            return retval;
        }
        else
        {
            throw UnivEX(3);
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
}

template <typename A>
A unvlist<A>::pop_front(void)
{
    try {
        if (numnode != 0)
        {
            numnode--;
            Node<A> *currentptr = nodeaddr->getTail();
            A retval = nodeaddr->Getdata();
            if (numnode != 0)
            {
                currentptr->AdjustHead(nullptr);
                nodeaddr->AdjustTail(nullptr);
                delete nodeaddr;
                nodeaddr = currentptr;
            }
            else
            {
                delete nodeaddr;
                nodeaddr = nullptr;
            }
            return retval;
        }
        else
        {
            throw UnivEX(3);
        }
    } catch (UnivEX &ex) {
        ex.What();
    }
}

template <typename A>
void unvlist<A>::push_back(const A &val)
{
    if (numnode != 0)
    {
        numnode++;
        Node<A> *currentptr = nodeaddr;
        while (currentptr->getTail() != nullptr)
        {
            currentptr = currentptr->getTail();
        }
        currentptr->NewTail();
        currentptr = currentptr->getTail();
        currentptr->Setdata(val);
    }
    else
    {
        numnode++;
        nodeaddr = new Node<A>;
        nodeaddr->Setdata(val);
    }
}

template <typename A>
void unvlist<A>::push_front(const A &val)
{
    if (numnode != 0)
    {
        numnode++;
        Node<A> *currentptr = new Node<A>;
        currentptr->Setdata(val);
        currentptr->AdjustTail(nodeaddr);
        nodeaddr->AdjustHead(currentptr);
        nodeaddr = currentptr;
    }
    else
    {
        numnode++;
        nodeaddr = new Node<A>;
        nodeaddr->Setdata(val);
    }
}

template <typename A>
unvlist<A> unvlist<A>::operator+(const unvlist<A> &Obj) // check numnode == 0
{
    Node<A> *currentptr = nodeaddr;
    unvlist<A> retval;
    if (numnode != 0)
    {
        while (currentptr->getTail() != nullptr)
        {
            retval.push_back(currentptr->Getdata());
            currentptr = currentptr->getTail();
        }
    }
    currentptr = Obj.nodeaddr;
    if (Obj.numnode != 0)
    {
        while (currentptr->getTail() != nullptr)
        {
            retval.push_back(currentptr->Getdata());
            currentptr = currentptr->getTail();
        }
    }
    return retval;
}

template <typename A>
bool unvlist<A>::operator==(const unvlist<A> &Obj)
{
    bool retval= false;
    if (numnode != Obj.numnode)
    {
        return retval;
    }
    else if (numnode == 0)
    {
        return true;
    }
    else
    {
        retval = true;
        Node<A> *ptr1 = nodeaddr;
        Node<A> *ptr2 = Obj.nodeaddr;
        while (ptr1->getTail() != nullptr)
        {
            if (ptr1->Getdata() != ptr2->Getdata())
            {
                retval = false;
                break;
            }
            ptr1 = ptr1->getTail();
            ptr2 = ptr2->getTail();
        }
        return retval;
    }
}
