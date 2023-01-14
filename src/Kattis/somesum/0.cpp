#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  cout << (n & 1 ? "Either" : n & 2 ? "Odd" : "Even") << endl;
  return 0;
}
