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
    for (int i = 0; i <= 13; i++)
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
  vector<vector<string>> players_card(players);
  vector<int> players_sum(players);

  for (int i = 0; i < players; i++)
  {
    players_card[i].push_back(draw_card());
    players_card[i].push_back(draw_card());
    players_sum[i] = parse_number(player_card[i][0]) + parse_number(player_card[i][1]);
    if (players_sum[i] > 21)
    {
      players_sum[i] = players_sum[i] - 10;
    }
  }

  house_card.push_back(draw_card());
  house_card.push_back(draw_card());
  house_sum = parse_number(house_card[0]) + parse_number(house_card[1]);
  if (house_sum > 21)
  {
    house_sum = house_sum - 10;
  }

  cout << "House: HIDDEN, " << house_card[1] << endl;
  for (int i = 0; i < players; i++)
  {
    cout << "Player" << i+1 << ": " << players_card[i][0] << ", " << players_card[i][1] << "(" << players_sum[i] << ")" << endl;
  }

  /*Player turn start*/
  for (int i = 0; i < players; i++)
  {
    cout << "---Player" << i+1 << " turn ---" << endl;



    cout << endl;
  }
  /*Player turn End*/

  /*House turn Start*/

  /*House turn End*/

  return 0;
}
