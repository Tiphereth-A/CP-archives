#include <bits/stdc++.h>
using namespace std;
string f(string s) {
  for (auto &ch : s) {
    if (isupper(ch)) ch = tolower(ch);
  }
  sort(s.begin(), s.end());
  return s;
}
int main() {
  map<string, int> cnt;
  vector<string> words;
  vector<string> ans;
  string s;
  while (cin >> s) {
    if (s == "#") break;
    words.push_back(s);
    cnt[f(s)]++;
  }
  for (auto const &s : words) {
    if (cnt[f(s)] == 1) ans.push_back(s);
  }
  sort(ans.begin(), ans.end());
  for (auto const &s : ans) cout << s << '\n';
  return 0;
}
