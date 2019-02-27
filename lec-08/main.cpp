//
//  main.cpp
//  univlist
//
//  Created by 장주현 on 2/20/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include "univ.hpp"

int main(void) {
    
    int *arr = new int[100];
    
    for (int i = 0; i < 100; i++)
    {
        arr[i] = 100 + i;
    }
    
    unvlist<int> intarr;
    //unvlist<int> intarr2(arr, 100);
    //unvlist<int> intarr3;
    
    for (int i = 0; i < 100; i++)
    {
        intarr.push_back(arr[i]);
        //intarr3.push_front(arr[i]);
    }

    //int b = intarr.pop_back();
    //std::cout << b << std::endl;
    //b = intarr.pop_front();
    //std::cout << b << std::endl;
    
    //int a = 5000;
    //intarr.set(50, a);
    
    //intarr.erase(39);
    
    /*unvlist<int> intarr4 =  intarr + intarr2;*/
    
    /*bool tf = (intarr == intarr2);
    std::cout << tf << std::endl;*/
    
    for (int i = 0; i < intarr.size(); i++)
    {
        std::cout << i << "th : " << intarr.get(i) << std::endl;
    }
    
    delete [] arr;
    
    return 0;
}
