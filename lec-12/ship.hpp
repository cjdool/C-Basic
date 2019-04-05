//
//  ship.hpp
//  BattleShip
//
//  Created by 장주현 on 2/27/19.
//  Copyright © 2019 장주현. All rights reserved.
//

#ifndef ship_h
#define ship_h

#include <string>
#include <vector>
#include <tuple>

class ship {
private:
    std::vector<std::pair<int,int>> positioncalculate (int x, int y, int vh)
    {
        std::vector<std::pair<int, int>> result;
        
        int currentx = x;
        int currenty = y;
        
        for (int i = 0; i < size; i++)
        {
            result.push_back(std::make_pair(currentx, currenty));
            if (vh == 0) // vertical
            {
                currentx = currentx + 1;
            }
            else // horizontal
            {
                currenty = currenty + 1;
            }
        }
        
        return result;
    }
protected:
    int size;
    std::string type;
    std::tuple<int, int, int> phead {-1,-1,-1};
public:
    void setposition (int x, int y, int vh)
    {
        phead = std::make_tuple(x, y, vh);
    }
    bool hitmiss(int x, int y)
    {
        bool result = false;
        int currentx = std::get<0>(phead);
        int currenty = std::get<1>(phead);
        
        for (int i = 0; i < size; i++)
        {
            if ((currentx == x) && (currenty == y))
            {
                result = true;
                break;
            }
            if (std::get<2>(phead) == 0) // vertical
            {
                currentx = currentx + 1;
            }
            else // horizontal
            {
                currenty = currenty + 1;
            }
        }
        return result;
    }
    std::vector<std::pair<int, int>> getinfo (void)
    {
        std::vector<std::pair<int, int>> emptyvector;
        if (std::get<0>(phead) != -1 && std::get<1>(phead) != -1 && std::get<2>(phead) != -1)
        {
            emptyvector = positioncalculate(std::get<0>(phead), std::get<1>(phead), std::get<2>(phead));
        }
        return emptyvector;
    }
    int getsize (void)
    {
        return size;
    }
    std::vector<std::pair<int, int>> estimatedpoint (int x, int y, int vh)
    {
        return positioncalculate(x, y, vh);
    }
    std::string gettype (void)
    {
        return type;
    }
};

class AircraftCarrier: public ship {
public:
    AircraftCarrier()
    {
        size = 6;
        type = "carrier";
    }
};

class Battleship: public ship {
public:
    Battleship()
    {
        size = 4;
        type = "battleship";
    }
};

class Submarine: public ship {
public:
    Submarine()
    {
        size = 3;
        type = "submarine";
    }
};

class Destroyer: public ship {
public:
    Destroyer()
    {
        size = 3;
        type = "destroyer";
    }
};

class PatrolBoat: public ship {
public:
    PatrolBoat()
    {
        size = 2;
        type = "patrolboat";
    }
};

#endif /* ship_h */
