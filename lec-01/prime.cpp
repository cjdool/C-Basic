#include <iostream>

using namespace std;

int main (void)
{
  bool isprime;
  int prime = 0;
  int n;
  cout << "How many [1..100]?  ";
  cin >> n;

  int i = 2;
  while(prime != n)
  {
    isprime = true;
    for (int j = 2; j < i; j++)
    {
      if ((i % j) == 0)
      {
        isprime = false;
        break;
      }
    }

    if (isprime)
    {
      cout << i << endl;
      prime++;
    }

    i++;
  }
  cout << "Total " << n << " primes found!" << endl;
}
