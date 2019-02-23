//
//  main.cpp
//  Exceptionhandle
//
//  Created by 장주현 on 2/21/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

char* account = "1234-5678";
int password = 1122;
int balance = 1000;

class AccountEx
{
public:
    AccountEx(char *input)
    {
        strcpy(errorreason, input);
    }
    AccountEx(char *input, int amount)
    {
        strcpy(errorreason, input);
        unenough = amount;
    }
    void Printout(void)
    {
        if (unenough > 0)
        {
            cout << errorreason << unenough << endl;
        }
        else
        {
            cout << errorreason << endl;
        }
    }
private:
    char errorreason[30];
    int unenough = 0;
};

int main(void)
{
    char input_accout[256];
    int input_password;
    int withdrawamout;
    
    cout << "Account? ";
    cin >> input_accout;
    cout << "PassWord? ";
    cin >> input_password;
    
    try {
        if ((strcmp(account, input_accout) == 0) && (password == input_password))
        {
            cout << "Withdraw? ";
            cin >> withdrawamout;
            try {
                if (balance - withdrawamout < 0)
                {
                    throw AccountEx("Insufficeint cash: ", withdrawamout - balance);
                }
                else
                {
                    balance = balance - withdrawamout;
                    cout << "Balance = " << balance << endl;
                }
            } catch (AccountEx &ex) {
                ex.Printout();
            }
        }
        else
        {
            throw AccountEx("Check your Input");
            
        }
    } catch (AccountEx &ex) {
        ex.Printout();
        cout << "Account: " << input_accout << endl;
        cout << "Password: " << input_password << endl;
    }
    
    return 0;
}
