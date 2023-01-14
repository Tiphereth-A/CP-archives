#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  stringstream ss;
  ss.precision(0);
  ss << fixed << pow(2.0L, n + 1);
  string str = ss.str();
  str[str.length() - 1]--;
  str[str.length() - 1]--;
  cout << str << endl;
  return 0;
}
