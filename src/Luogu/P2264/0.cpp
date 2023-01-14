#include <bits/stdc++.h>
using namespace std;
bool use[2010];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<string> word(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> word[i];
    transform(word[i].begin(), word[i].end(), word[i].begin(), ::tolower);
  }
  string s, __;
  getline(cin, s);
  getline(cin, s);
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  int tot = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '.') {
      for (int j = 1; j <= n; ++j)
        if (__ == word[j] && !use[j]) {
          use[j] = 1;
          ++tot;
          break;
        }
      __ = "";
      memset(use, 0, sizeof(use));
      continue;
    }
    if (s[i] == ',') {
      for (int j = 1; j <= n; ++j)
        if (__ == word[j] && !use[j]) {
          use[j] = 1;
          ++tot;
          break;
        }
      __ = "";
      continue;
    }
    if (s[i] == ' ') {
      for (int j = 1; j <= n; ++j)
        if (__ == word[j] && !use[j]) {
          use[j] = 1;
          ++tot;
          break;
        }
      __ = "";
      continue;
    }
    __ += s[i];
  }
  cout << tot;
  return 0;
}
