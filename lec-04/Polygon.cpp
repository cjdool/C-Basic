//
//  main.cpp
//  Polygon
//
//  Created by 장주현 on 1/7/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

class Point
{
public:
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(float a, float b)
    {
        x = a;
        y = b;
    }
    float getX_Point(void)
    {
        return x;
    }
    float getY_Point(void)
    {
        return y;
    }
    void set_Point(float a, float b)
    {
        x = a;
        y = b;
    }
private:
    float x;
    float y;
};

class Polygon
{
public:
    Polygon()
    {
        angle = 0;
    }
    Polygon(vector<Point> &vec)
    {
        angle = vec.size();
        point_vector = vec;
    }
    ~Polygon()
    {
        point_vector.clear();
    }
    void set_Polygon(vector<Point> &vec)
    {
        angle = vec.size();
        point_vector = vec;
    }
    long get_angleValue(void)
    {
        return angle;
    }
    vector<Point> get_pointValue(void)
    {
        return point_vector;
    }
protected:
    vector<Point> point_vector;
    long angle;
};

class Rectangle : public Polygon
{
public:
    Rectangle()
    {
        angle = 2;
        point_vector.reserve(2);
    }
    Rectangle(vector<Point> &vec) : Polygon(vec)
    {
        if (vec.size() != 2)
        {
            cout << "Error is occured in assigning value" << endl;
        }
    }
    void set_Rectangle(vector<Point> &vec)
    {
        if (vec.size() != 2)
        {
            cout << "Error is occured in assigning value" << endl;
        }
        set_Polygon(vec);
    }
    float get_Row(void)
    {
        return fabs(point_vector.at(0).getX_Point() - point_vector.at(1).getX_Point());
    }
    float get_Col(void)
    {
        return fabs(point_vector.at(0).getY_Point() - point_vector.at(1).getY_Point());
    }
    float Calculate_Size(void)
    {
        return get_Col() * get_Row();
    }
};

int main (void)
{
    char str_buff[128];
    string input;
    vector<float> v1;
    vector<Point> rec_p(2);
    cout << "Please enter Rectangle point" << endl;
    getline(cin, input);
    strcpy(str_buff, input.c_str());
    char* tok  = strtok(str_buff, ",");
    while (tok != nullptr)
    {
        v1.push_back(atof(tok));
        tok = strtok(nullptr, ",");
    }
    rec_p.at(0).set_Point(v1.at(0), v1.at(1));
    rec_p.at(1).set_Point(v1.at(2), v1.at(3));
    //Rectangle r1 = Rectangle(rec_p);
    Rectangle r1;
    r1.set_Rectangle(rec_p);
    cout << "Rectangle Size is " << r1.Calculate_Size() << endl;
    
    return 0;
}
