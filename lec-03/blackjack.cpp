#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
vector<string> cards;
int players

void swap(int i, int j)
{
  auto n = cards[i];
  cards[i] = cards[j];
  cards[j] = n;
}

string draw_card()
{
  string str = cards.back();
  cards.pop_back();
  return str;
}

void shuffle_cards()
{
  for (int i = 0; i < 1000; i++)
  {
    swap(rand() % cards.size(), rand() % cards.size());
  }
}

int parse_number(string trump)
{
  string temp = trump.pop_back(0);
  int value;
  if (temp.compare("A") == 0)
    value = 11;
  else if (temp.compare("J") == 0)
    value = 10;
  else if (temp.compare("Q") == 0)
    value = 10;
  else if (temp.compare("K") == 0)
    value = 10;
  else
    value = stoi(temp);

  return value;
}

string choose_hit (int sum)
{
  string output;
  int is_hit = rand() % 2;
  if (sum > 17)
  {
    output = "Stand";
  }
  else if (sum < 14)
  {
    output = "Hit";
  }
  else
  {
    if (is_hit == 1)
    {
      output = "Hit";
    }
    else // is_hit == 0
    {
      output = "Stand";
    }
  }
  cout << output << endl;
  return output;
}

void hit_handler(vector<string> &card, int &p_sum)
{
  int temp_sum = p_sum + parse_number(card.back());

}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Command Line Error!" << endl;
    exit(0);
  }
  /*Game Setting*/
  int decks = 4;
  int seed = stoi(argv[1]);
  players = stoi(argv[2]);

  if (players < 1)
  {
    cout << "Player Must be at least one person" << endl;
    exit(0);
  }

  srand(seed);

  for (int j = 0; j < decks; j++)
  {
    for (int i = 1; i <= 13; i++)
    {
      string cardnum;
      if (i == 1)
        cardnum = "A";
      else if (i == 11)
        cardnum == "J";
      else if (i == 12)
        cardnum == "Q";
      else if (i == 13)
        cardnum == "K";
      else
        cardnum = to_string(i);
      cards.push_back(cardnum + "c");
      cards.push_back(cardnum + "h");
      cards.push_back(cardnum + "d");
      cards.push_back(cardnum + "s");
    }
  }
  shuffle_cards();
  /*Game Setting End*/

  /*Game Start*/
  vector<string> house_card;
  int house_sum;
  string house_result;
  vector<vector<string>> players_card(players);
  vector<int> players_sum(players);
  vector<string> player_result(players);

  /*!st Card dispense*/
  for (int i = 0; i < players; i++)
  {
    players_card[i].push_back(draw_card());
  }
  house_card.push_back(draw_card());

  /*2nd Card dispense*/
  for (int i = 0; i < players; i++)
  {
    players_card[i].push_back(draw_card());
    players_sum[i] = parse_number(player_card[i][0]) + parse_number(player_card[i][1]);
    if (players_sum[i] > 21)
    {
      players_sum[i] = players_sum[i] - 10;
    }
  }
  house_card.push_back(draw_card());
  house_sum = parse_number(house_card[0]) + parse_number(house_card[1]);
  if (house_sum > 21)
  {
    house_sum = house_sum - 10;
  }

  /*Print out result of 1st,2nd card*/
  cout << "House: HIDDEN, " << house_card[1] << endl;
  for (int i = 0; i < players; i++)
  {
    cout << "Player" << i+1 << ": " << players_card[i][0] << ", " << players_card[i][1] << "(" << players_sum[i] << ")" << endl;
  }

  /*Each Turn is Started*/
  string user_input;
  if (house_sum == 21) // this case immediate end of game
  {
    house_result = "Win";
    for (int i = 0; i < players; i++)
    {
      player_result[i] = "Lose";
    }
  }
  else  // start with players turn
  {
    /*Player turn start*/
    for (int i = 0; i < players; i++)
    {
      cout << "--- Player" << i+1 << " turn ---" << endl;
    
      while(1) // player 1 turn loop
      {
        cout << "Player" << i+1 << ": ";
        for (auto &n: player_card[i])
        {
          cout << n << ", ";
        }
        cout << "(" << player_sum[i] << ")" << endl;
        if (i == 0)
        {
          getline(cin, user_input);
        }
        else
        {
          user_input = choose_hit(players_sum[i]);
        }

        if (user_input.compare("Hit") == 0)
        {
          player_card[i].push_back(draw_card());
          hit_handler(player_card[i], player_sum[i]);

          if (player_sum[i] > 21) // burst case
          {
            player_result[i] = "Lose";
            break;
          }
          else // not over 21 -> re-entered by user
          {
            continue;
          }
        }
        else if (user_input.compare("Stand") == 0)
        {
          break;
        }
        else
        {
          cout << "Wrong Order, Only Hit and Stand available, Try Again" << endl;
        }
      } // end of one player turn loop
      cout << "Player" << i+1 << ": ";
      for (auto &n: player_card[i])
      {
        cout << n << ", ";
      }
      cout << "(" << player_sum[i] << ")" << endl << endl;
    }
    /*end of players turn*/ 
    /*House turn Start*/
    string house_input;
    cout << "--- House turn ---" << endl;
    while(1)
    {
      cout << "House: ";
      for (auto &n: house_card)
      {
        cout << n << ", ";
      }
      cout << "(" << house_sum << ")" << endl;

      if (house_sum > 16)
      {
        house_input = "Stand";
      }
      else
      {
        house_input = "Hit";
      }
      cout << house_input << endl;

      if (house_input.compare("Hit") == 0)
      {
        house_card.push_back(draw_card());
        hit_handler(house_card, house_sum);

        if (house_sum > 21)
        {
          break;
        }
        else
        {
          continue;
        }
      }
      else // Stand Case
      {
        break;
      }
    }
    cout << "House: ";
    for (auto &n: house_card)
    {
      cout << n << ", ";
    }
    cout << "(" << house_sum << ")" << endl;

    /*House turn End*/
  } // End of Actual Game

  /*Calculate Result*/

  /*Print out Result*/
  cout << "---   Game Result   ---" << endl;
  cout << "House: ";
  for (auto &n; house_card)
  {
    cout << n << ", ";
  }

  return 0;
}
