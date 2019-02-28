//
//  main.cpp
//  Calculator
//
//  Created by 장주현 on 2/26/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

class Calculator {
private:
    string infix;
    stack<int> operand;
    stack<char> operation;
    queue<char> postfix;
    int operPriority(char c);
public:
    Calculator(string s)
    {
        infix = s;
    }
    void setPostfix(void);
    void calculate(void);
    void printResult(void);
};

int Calculator::operPriority(char c)
{
    if ((c == '+') || (c == '-'))
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void Calculator::setPostfix(void)
{
    auto n = infix.length();
    char char_array[n+1];
    strcpy(char_array, infix.c_str());
    int start = 0;
    while (char_array[start] != '\0')
    {
        if ((char_array[start] == '+') || (char_array[start] == '-') || (char_array[start] == '*') || (char_array[start] == '/'))
        {
            char comp = char_array[start];
            postfix.push(' ');
            if (operation.empty())
            {
                operation.push(comp);
            }
            else if (operPriority(operation.top()) < operPriority(comp))
            {
                operation.push(comp);
            }
            else // this program only 2 kind of priority -> do not have to have iteration
            {
                char temp = operation.top();
                operation.pop();
                postfix.push(temp);
                postfix.push(' ');
                operation.push(comp);
            }
        }
        else
        {
            postfix.push(char_array[start]);
        }
        start++;
    }
    while (!operation.empty())
    {
        char temp2 = operation.top();
        operation.pop();
        postfix.push(' ');
        postfix.push(temp2);
    }
}

void Calculator::calculate(void)
{
    string a;
    char itr;
    while (!postfix.empty())
    {
        itr = postfix.front();
        postfix.pop();
        if ((itr == '+') || (itr == '-') || (itr == '*') || (itr == '/'))
        {
            int post = operand.top();
            operand.pop();
            int pre = operand.top();
            operand.pop();
            if (itr == '+')
            {
                operand.push(pre + post);
            }
            else if (itr == '-')
            {
                operand.push(pre - post);
            }
            else if (itr == '*')
            {
                operand.push(pre * post);
            }
            else // itr == '/'
            {
                operand.push(pre / post);
            }
            if (!postfix.empty())
            {
                postfix.pop();
            }
        }
        else if (itr == ' ')
        {
            operand.push(stoi(a));
            a.clear();
        }
        else
        {
            a.push_back(itr);
        }
    }
}

void Calculator::printResult(void)
{
    cout << infix << "=" << operand.top() << endl;
    operand.pop();
}

int main(void) {
    string input; //= "1+2*3/4-6";
    cin >> input;
    Calculator calc(input);
    calc.setPostfix();
    calc.calculate();
    calc.printResult();
    
    return 0;
}
