#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
vector<string> cards;

void swap(int i, int j)
{

}

void shuffle_cards()
{
  string str;
  return str;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Command Line Error!" << endl;
    exit(0);
  }
  int seed = stoi(argv[1]);
  int decks = stoi(argv[2]);

  cout << seed << ' ' << decks << endl;
  int i = 10;
  string card = to_string(i) + "s";
  cout << card << endl;

  int sum = 0;
  sum += stoi(card);
  cout << sum << endl;

  return 0;
}
