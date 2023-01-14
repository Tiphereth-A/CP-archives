#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
unordered_set<string> dict;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  _for(i, 1, n) {
    getline(cin, s);
    char op = s[0];
    s.erase(s.begin(), s.begin() + 4 + (op == 'f'));
    if (op == 'a') dict.insert(s);
    else cout << (dict.count(s) ? "yes" : "no") << endl;
  }
  return 0;
}
