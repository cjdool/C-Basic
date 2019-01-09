//
//  stack.cpp
//  Stack Template
//
//  Created by 장주현 on 1/8/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    int topidx;
    int size;
    T* stackptr;
public:
    Stack(int asn);
    void Push(const T &ptr);
    T Pop();
    ~Stack()
    {
        delete[] stackptr;
    }
};

template <typename T>
Stack<T>::Stack(int asn)
{
    size = asn;
    topidx = 0;
    stackptr = new T[size];
}

template <typename T>
void Stack<T>::Push(const T &ptr)
{
    if (topidx == size) // memory over case
    {
        size = size * 2;
        T* temp = new T[size];
        for(int i = 0; i < topidx; i++)
        {
            temp[i] = stackptr[i];
        }
        delete[] stackptr;
        
        /*size = size * 2;
        stackptr = new T[size];
        for(int i = 0; i < topidx; i++)
        {
            stackptr[i] = temp[i];
        }
        delete[] temp;*/
        stackptr = temp;
    }
    stackptr[topidx] = ptr;
    topidx++;
}
template <typename T>
T Stack<T>::Pop(void)
{
    topidx--;
    T temp = stackptr[topidx];
    return temp;
}

int main(int argc, const char * argv[]) {
    Stack<char> stack1(10);
    //Stack<int> stack2(10);
    for (int i = 0; i < 12; i++)
    {
        stack1.Push(83-i);
    }
    //stack1.Push(83);
    //stack2.Push(83);
    //stack1.Push(67);
    //stack2.Push(67);
    for (int i = 0; i < 12; i++)
    {
        cout << stack1.Pop() << endl;
        //cout << stack2.Pop() << endl;
    }
    return 0;
}
