//
//  main.cpp
//  BattleShip
//
//  Created by 장주현 on 2/27/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#include <iostream>
#include <map>
#include "ship.hpp"

#define Acount 1
#define Bcount 2
#define Scount 2
#define Dcount 1
#define Pcount 4
#define rowSize 10
#define columnSize 10

std::map<char, std::vector<ship*>> board;

bool isOverlap (std::vector<std::pair<int, int>> &epoints)
{
    for (auto &m:epoints)
    {
        if ((m.first >= rowSize) || (m.second >= columnSize))
        {
            return true;
        }
    }
    std::vector<ship*> column;
    std::map<char, std::vector<ship*>>::const_iterator j;
    std::vector<ship*>::const_iterator i;
    j = board.begin();
    while (j != board.end())
    {
        column = j->second;
        i = column.begin();
        while (i != column.end())
        {
            for (auto &n:(*i)->getinfo())
            {
                for (auto &m:epoints)
                {
                    if (((n.first == m.first) && (n.second == m.second)))
                    {
                        return true;
                    }
                }
            }
            i++;
        }
        j++;
    }
    return false;
}

bool inputvalidation (std::string uinput, std::vector<std::pair<int, int>> &misspoint, std::vector<std::pair<int, int>> &hitpoint)
{
    bool result;
    int y = uinput.at(0) - 'A';
    if ((0 <= y) && (y < rowSize))
    {
        uinput.erase(0,1);
        try {
            int x = std::stoi(uinput) - 1;
            if ((0 <= x) && (x < columnSize))
            {
                result = true;
                for(auto &m:misspoint)
                {
                    if ((m.first == x) && (m.second == y))
                    {
                        result = false;
                        break;
                    }
                }
                for(auto &n:hitpoint)
                {
                    if ((n.first == x) && (n.second == y))
                    {
                        result = false;
                        break;
                    }
                }
            }
            else
            {
                result = false;
            }
        }
        catch (std::exception ex)
        {
            std::cout << ex.what() << std::endl;
            result = false;
        }
    }
    else
    {
        result = false;
    }
    return result;
}

std::string getLabel (std::vector<std::pair<int, int>> &misspoint, std::vector<std::pair<int, int>> &hitpoint, int x, int y)
{
    std::string result = "   ";
    std::vector<ship*> column;
    std::map<char, std::vector<ship*>>::const_iterator j;
    std::vector<ship*>::const_iterator i;
    j = board.begin();
    while (j != board.end())
    {
        column = j->second;
        i = column.begin();
        while (i != column.end())
        {
            for (auto &n:(*i)->getinfo())
            {
                if ((n.first == x) && (n.second == y))
                {
                    result.clear();
                    result.push_back(' ');
                    for (auto &m:hitpoint)
                    {
                        if ((m.first == x) && (m.second == y))
                        {
                            result.push_back('X');
                            break;
                        }
                    }
                    result.push_back(j->first);
                    if (result.length() != 3)
                    {
                        result.push_back(' ');
                    }
                    return result;
                }
            }
            i++;
        }
        j++;
    }
    for (auto &m:misspoint)
    {
        if ((m.first == x) && (m.second == y))
        {
            result = " X ";
            break;
        }
    }
    return result;
}

void displayboard (std::vector<std::pair<int, int>> &misspoint, std::vector<std::pair<int, int>> &hitpoint)
{
    for (int i = 0; i < rowSize+1; i++)
    {
        if (i == 0)
        {
            std::cout << "       A    B    C    D    E    F    G    H    I    J" << std::endl;
            std::cout << "      ---  ---  ---  ---  ---  ---  ---  ---  ---  ---" << std::endl;
            continue;
        }
        else
        {
            std::cout << i;
            if (i > 9)
            {
                std::cout << " |";
            }
            else
            {
                std::cout << "  |";
            }
        }
        for (int j = 0; j < columnSize; j++)
        {
            std::cout << "  " << getLabel(misspoint, hitpoint, i-1, j);
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "Command Line Error!" << std::endl;
        exit(1);
    }
    
    /*Game Setting*/
    /*1. Argument Parsing*/
    int score = 0;
    int seed = atoi(argv[1]);
    unsigned int numbomb = atoi(argv[2]);
    bool isdebug;
    if (argv[3][0] == 'd')
    {
        isdebug = true;
    }
    else
    {
        isdebug = false;
    }
    srand(seed);
    /*1. Argument Parsing Done*/
    
    /*2. Making Ship Instance*/
    std::vector<ship*> column;
    
    for (int i = 0; i < Pcount; i++)
    {
        column.push_back(new PatrolBoat);
    }
    board['P'] = column;
    column.clear();
    
    for (int i = 0; i < Dcount; i++)
    {
        column.push_back(new Destroyer);
    }
    board['D'] = column;
    column.clear();
    
    for (int i = 0; i < Scount; i++)
    {
        column.push_back(new Submarine);
    }
    board['S'] = column;
    column.clear();
    
    for (int i = 0; i < Bcount; i++)
    {
        column.push_back(new Battleship);
    }
    board['B'] = column;
    column.clear();
    
    for (int i = 0; i < Acount; i++)
    {
        column.push_back(new AircraftCarrier);
    }
    board['A'] = column;
    column.clear();
    /*3. Making Ship Instance Done*/
    
    /*4. Position Ship*/
    std::map<char, std::vector<ship*>>::const_iterator j;
    std::vector<ship*>::const_iterator i;
    j = board.begin();
    while (j != board.end())
    {
        column = j->second;
        i = column.begin();
        while (i != column.end())
        {
            int x = rand() % rowSize; // A-J
            int y = rand() % columnSize; // 1-10
            int vh = rand() % 2; // 0-1 (vertical or horizontal)
            
            auto epoints = (*i)->estimatedpoint(x, y, vh);
            
            if (isOverlap(epoints) == false)
            {
                (*i)->setposition(x, y, vh);
                i++;
            }
            else
            {
                continue;
            }
        }
        j++;
    }
    /*4. Position Ship Done*/
    
    /*Game Setting End*/
    
    /*Game Start*/
    std::cout << "===== Game Start =====" << std::endl;
    unsigned int bombcount = numbomb;
    std::vector<std::pair<int, int>> misspoint;
    std::vector<std::pair<int, int>> hitpoint;
    if (isdebug)
    {
        displayboard(misspoint, hitpoint);//display board
    }
    while (bombcount != 0)
    {
        std::string userinput;
        getline(std::cin, userinput);
        if (inputvalidation(userinput, misspoint, hitpoint)) //validate userinput
        {
            bool hitmiss = false;
            int yinput = userinput.at(0) - 'A';
            userinput.erase(0,1);
            int xinput = std::stoi(userinput) - 1;
            j = board.begin();
            while (j != board.end())
            {
                column = j->second;
                i = column.begin();
                while (i != column.end())
                {
                    if ((*i)->hitmiss(xinput, yinput))
                    {
                        hitmiss = true;
                        hitpoint.push_back(std::make_pair(xinput, yinput));
                        score += (*i)->getsize();
                        std::cout << "hit on " << (*i)->gettype() << std::endl << std::endl;
                        break;
                    }
                    else
                    {
                        i++;
                    }
                }
                if (hitmiss == true)
                {
                    break;
                }
                j++;
            }
            if (hitmiss == false)
            {
                misspoint.push_back(std::make_pair(xinput, yinput));
                std::cout << "miss" << std::endl << std::endl;
            }
            
            bombcount--;
        }
        else
        {
            std::cout << "Wrong Input, Try Again" << std::endl << std::endl;
        }
        
        if (isdebug)
        {
            displayboard(misspoint, hitpoint);//display board
        }
    }
    /*Game End*/
    
    /*Print out Score*/
    std::cout << std::endl;
    if (!isdebug)
    {
        displayboard(misspoint, hitpoint);
    }
    std::cout << "Score: " << score << std::endl;
    /*Print out Score End*/
    
    /*Clear Memory*/
    
    j = board.begin();
    while (j != board.end())
    {
        column = j->second;
        for (auto &n: column)
        {
            delete n;
        }
        j++;
    }
    
    return 0;
}
