#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main (void)
{
  string input_string;
  cout << "input: ";
  getline(cin, input_string);

  stringstream ss(input_string);
  string tok;
  vector<string> v1;

  while(ss >> tok)
  {
    v1.push_back(tok);
  }

  int count = v1.size();
  
  for(int i = 1; i <= count; i++)
  {
    cout << v1[count-i] << endl;
  }

  return 0;
}
