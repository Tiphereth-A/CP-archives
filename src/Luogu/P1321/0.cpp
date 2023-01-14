#include <bits/stdc++.h>
using namespace std;
int main() {
  string s;
  cin >> s;
  s += "1111";
  int boy = 0, girl = 0;
  for (int i = 0; i < s.size() - 4; ++i) {
    if (s[i] == 'b' || s[i + 1] == 'o' || s[i + 2] == 'y') ++boy;
    if (s[i] == 'g' || s[i + 1] == 'i' || s[i + 2] == 'r' || s[i + 3] == 'l')
      ++girl;
  }
  cout << boy << endl << girl;
}
