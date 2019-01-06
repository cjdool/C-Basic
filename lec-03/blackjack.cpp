#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
vector<string> cards;
int players;

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
  string temp = trump.substr(0, trump.size()-1);
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

int check_ace(vector<string> &card)
{
  int ace_count = 0;
  for (auto &x : card)
  {
    char temp = x.at(0);
    if (temp == 'A')
    {
      ace_count++;
      break;
    }
  }
  return ace_count;
}


void hit_handler(vector<string> &card, int &p_sum)
{
  int temp_sum = p_sum + parse_number(card.back());
  if (temp_sum > 21) // over 21 -> check ace case
  {
    int ace_count = check_ace(card);
    if (ace_count != 0)
    {
      int max_sum = 0;
      for (auto &x: card)
      {
        max_sum += parse_number(x);
      }
      if ((max_sum - 10 * ace_count) < 22)
      {
        for (int i = 1; i <= ace_count; i++)
        {
          if ((max_sum - 10 * i) < 22)
          {
            p_sum = max_sum - 10 * i;
            break;
          }
        }
      }
      else // bust
      {
        p_sum = max_sum - 10 * ace_count;
      }
    }
    else // no ace case
    {
      p_sum = temp_sum;
    }
  }
  else // not over 21 -> just return value
  {
    p_sum = temp_sum;
  }
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
        cardnum = "J";
      else if (i == 12)
        cardnum = "Q";
      else if (i == 13)
        cardnum = "K";
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
  vector<vector<string>> players_card(players);
  vector<int> players_sum(players);
  vector<string> players_result(players);

  /*1st Card dispense*/
  for (int i = 0; i < players; i++)
  {
    players_card[i].push_back(draw_card());
    players_sum[i] = parse_number(players_card[i][0]);
  }
  house_card.push_back(draw_card());
  house_sum = parse_number(house_card[0]);

  /*2nd Card dispense*/
  for (int i = 0; i < players; i++)
  {
    players_card[i].push_back(draw_card());
    hit_handler(players_card[i], players_sum[i]);
  }
  house_card.push_back(draw_card());
  hit_handler(house_card, house_sum);

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
    for (int i = 0; i < players; i++)
    {
      players_result[i] = "Lose";
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
        for (auto &n: players_card[i])
        {
          cout << n << ", ";
        }
        cout << "(" << players_sum[i] << ")" << endl;
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
          players_card[i].push_back(draw_card());
          hit_handler(players_card[i], players_sum[i]);

          if (players_sum[i] > 21) // burst case
          {
            players_result[i] = "Lose";
            break;
          }
          else // not over 21 -> re-entered by user
          {
            continue;
          }
        }
        else if (user_input.compare("Stand") == 0)
        {
          players_result[i] = "Stand";
          break;
        }
        else
        {
          cout << "Wrong Order, Only Hit and Stand available, Try Again" << endl;
        }
      } // end of one player turn loop
      cout << "Player" << i+1 << ": ";
      for (auto &n: players_card[i])
      {
        cout << n << ", ";
      }
      cout << "(" << players_sum[i] << ")" << endl << endl;
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
    cout << "(" << house_sum << ")" << endl << endl;
    /*House turn End*/
  } // End of Actual Game

  /*Calculate Result*/
  int index = 0;
  for (auto &x : players_result)
  {
    if (x.compare("Stand") == 0)
    {
      if (house_sum > 21)
      {
        x = "Win";
      }
      else
      {
        if (house_sum < players_sum[index])
        {
          x = "Win";
        }
        else if (house_sum == players_sum[index])
        {
          x = "Draw";
        }
        else
        {
          x = "Lose";
        }
      }
    }
    index++;
  }

  /*Print out Result*/
  cout << "---   Game Result   ---" << endl;
  cout << "House: ";
  for (auto &n : house_card)
  {
    cout << n << ", ";
  }
  cout << "(" << house_sum << ")";
  if (house_sum > 21)
  {
    cout << " - Bust !!";
  }
  cout << endl;
  // end of House Result
  for (int i = 0; i < players; i++)
  {
    cout << "[" << players_result[i] << "] " << "Player" << i+1 << ": ";
    for (auto &n: players_card[i])
    {
      cout << n << ", ";
    }
    cout << "(" << players_sum[i] << ")";
    if (players_sum[i] > 21)
    {
      cout << " - Bust !!";
    }
    cout << endl;
  }

  return 0;
}
