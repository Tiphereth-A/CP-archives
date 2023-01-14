#include <bits/stdc++.h>
using namespace std;
const char mp[] = "2223334445556667 77888999";
int main() {
  ios::sync_with_stdio(false);
  string s;
  cin >> s;
  string tmp;
  vector<string> dict;
  while (cin >> tmp) dict.push_back(tmp);
  int len = s.size();
  bool gf = false;
  for (int i = 0; i < dict.size(); i++) {
    if (len != dict[i].size()) continue;
    bool f = true;
    for (int j = 0; j < len; j++)
      if (mp[dict[i][j] - 'A'] != s[j]) {
        f = false;
        break;
      }
    if (f) {
      cout << dict[i] << '\n';
      gf = true;
    }
  }
  if (!gf) cout << "NONE\n";
}
