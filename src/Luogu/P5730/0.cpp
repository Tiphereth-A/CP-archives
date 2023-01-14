#include <bits/stdc++.h>
using namespace std;
const char num[10][5][4] = {{"XXX", "X.X", "X.X", "X.X", "XXX"},
                            {"..X", "..X", "..X", "..X", "..X"},
                            {"XXX", "..X", "XXX", "X..", "XXX"},
                            {"XXX", "..X", "XXX", "..X", "XXX"},
                            {"X.X", "X.X", "XXX", "..X", "..X"},
                            {"XXX", "X..", "XXX", "..X", "XXX"},
                            {"XXX", "X..", "XXX", "X.X", "XXX"},
                            {"XXX", "..X", "..X", "..X", "..X"},
                            {"XXX", "X.X", "XXX", "X.X", "XXX"},
                            {"XXX", "X.X", "XXX", "..X", "XXX"}};
int main() {
  int n;
  cin >> n;
  char ch;
  string s[5];
  while (n--) {
    cin >> ch;
    for (int i = 0; i < 5; ++i) s[i] += num[ch - '0'][i];
    if (n)
      for (int i = 0; i < 5; ++i) s[i] += '.';
  }
  for (int i = 0; i < 5; ++i) cout << s[i] << endl;
  return 0;
}
