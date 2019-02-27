//
//  main.cpp
//  contact
//
//  Created by 장주현 on 2/26/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main(void)
{
    //cout << "For Xcode Debug" << endl;
    string input;
    map<string, string> contactdb;
    map<string, string>::const_iterator i;
    while (1)
    {
        getline(cin, input);
        string cmd;
        stringstream ss(input);
        ss >> cmd;
        if (cmd == "show")
        {
            i = contactdb.begin();
            while (i != contactdb.end())
            {
                cout << "\t\t" << i->first << " " << i->second << endl;
                i++;
            }
        }
        else if (cmd == "add")
        {
            string name;
            string number;
            ss >> name;
            ss >> number;
            if ( contactdb.find(name) == contactdb.end())
            {
                contactdb.emplace(make_pair(name, number));
            }
            else
            {
                cout << name << " is already in contact list" << endl;
            }
        }
        else if (cmd == "find")
        {
            string name;
            ss >> name;
            if (contactdb.find(name) == contactdb.end())
            {
                cout << name << " is not exist" << endl;
                
            }
            else
            {
                i = contactdb.find(name);
                cout << "\t\t" << i->second << endl;
            }
        }
        else if (cmd == "delete")
        {
            string name;
            ss >> name;
            if (contactdb.find(name) == contactdb.end())
            {
                cout << name << " is not exist" << endl;
                
            }
            else
            {
                contactdb.erase(name);
            }
        }
        else if (cmd == "exit")
        {
            cout << "Bye" << endl;
            break;
        }
        else
        {
            cout << "Incorrect Syntax, Try Proper Input" << endl;
        }
    }
    return 0;
}
