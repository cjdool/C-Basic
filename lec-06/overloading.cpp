//
//  main.cpp
//  Overloading
//
//  Created by 장주현 on 2/17/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class Time {
public:
    Time()
    {
        hours = 0;
        mins = 0;
        secs = 0;
    }
    Time(int h, int m, int s)
    {
        hours = h;
        mins = m;
        secs = s;
    }
    void showcurrenttime(void)
    {
        cout << hours << ":" << mins << ":" << secs << endl;
    }
    tuple<int, int, int> operator+ (const Time &Obj)
    {
        int temp_sec = secs + Obj.secs;
        int temp_min = mins + Obj.mins;
        int temp_hours = hours + Obj.hours;
        if (temp_sec > 59)
        {
            temp_sec = temp_sec - 60;
            temp_min++;
        }
        if (temp_min > 59)
        {
            temp_min = temp_min - 60;
            temp_hours++;
        }
        if (temp_hours > 23)
        {
            temp_hours = temp_hours - 24;
        }
        return make_tuple(temp_hours, temp_min, temp_sec);
    }
    tuple<int, int, int> operator- (const Time &Obj)
    {
        int temp_hours;
        int temp_min;
        int temp_sec;
        
        temp_sec = secs - Obj.secs;
        temp_min = mins - Obj.mins;
        temp_hours = hours - Obj.hours;
        if (temp_sec < 0)
        {
            temp_sec = temp_sec + 60;
            temp_min--;
        }
        if (temp_min < 0)
        {
            temp_min = temp_min + 60;
            temp_hours--;
        }
        
        return make_tuple(temp_hours, temp_min, temp_sec);
    }
    tuple<int, int, int> operator++ (int x) // x does not have meaning
    {
        int temp_hours = hours + 1;
        if (temp_hours > 23)
        {
            temp_hours = temp_hours - 24;
        }
        return make_tuple(temp_hours, mins, secs);
    }
    tuple<int, int, int> operator-- (void)
    {
        int temp_hours = hours - 1;
        if (temp_hours < 0)
        {
            temp_hours = temp_hours + 24;
        }
        return make_tuple(temp_hours, mins, secs);
    }
private:
    int hours;
    int mins;
    int secs;
};

int main(void) {
    Time T1, T2;
    string time;
    string input_hours;
    string input_mins;
    string input_secs;
    tuple<int, int, int> onlyforprint;
    
    cout << "Enter First Time  : ";
    getline(cin, time);
    stringstream ipstream(time);
    getline(ipstream, input_hours, ':');
    getline(ipstream, input_mins, ':');
    getline(ipstream, input_secs, ':');
    T1 = Time(stoi(input_hours), stoi(input_mins), stoi(input_secs));
    cout << "Enter Second Time : ";
    getline(cin, time);
    stringstream secondstream(time);
    getline(secondstream, input_hours, ':');
    getline(secondstream, input_mins, ':');
    getline(secondstream, input_secs, ':');
    T2 = Time(stoi(input_hours), stoi(input_mins), stoi(input_secs));
    
    T1.showcurrenttime();
    T2.showcurrenttime();
    
    onlyforprint = T1 + T2;
    cout << "+ operation : " << get<0>(onlyforprint) << ":" << get<1>(onlyforprint) << ":" << get<2>(onlyforprint) << endl;
    onlyforprint = T1 - T2; // suppose T1 > T2
    cout << "- operation : " << get<0>(onlyforprint) << ":" << get<1>(onlyforprint) << ":" << get<2>(onlyforprint) << endl;
    onlyforprint = T1++;
    cout << "++ operation : " << get<0>(onlyforprint) << ":" << get<1>(onlyforprint) << ":" << get<2>(onlyforprint) << endl;
    onlyforprint = --T2;
    cout << "-- operation : " << get<0>(onlyforprint) << ":" << get<1>(onlyforprint) << ":" << get<2>(onlyforprint) << endl;
    
    return 0;
}
