#include <bits/stdc++.h>
using namespace std;
const string key[3] = {"qwertyuiop", "asdfghjkl;", "zxcvbnm,./"};
string ans;
string f(int dir, string str) {
  string s1;
  for (int i = 0; i < str.size(); i++) {
    int j, p;
    for (j = 0; j < 3; j++)
      if ((p = key[j].find(str[i])) != string::npos) break;
    p += dir;
    if ((p < 0) || (p >= 10)) return f(-dir, str);
    s1 += key[j][p];
  }
  return s1;
}
int main() {
  char dir;
  cin >> dir;
  int d;
  if (dir == 'R') d = -1;
  else if (dir == 'L') d = 1;
  string c;
  cin >> c;
  ans = f(d, c);
  cout << ans;
  return 0;
}
