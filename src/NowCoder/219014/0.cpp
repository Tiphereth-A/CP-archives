#include <bits/stdc++.h>
using namespace std;
map<string, string> dict;
int main() {
  int n;
  cin >> n;
  cin.ignore();
  string a, b;
  while (n--) {
    cin >> a;
    cin.ignore();
    getline(cin, b);
    dict[a] = b;
  }
  int m;
  cin >> m;
  cin.ignore();
  string s;
  while (m--) {
    getline(cin, s);
    int last = 0;
    string ftxt;
    for (int i = 0; i < s.size(); ++i)
      if (s[i] == ' ' || i == s.size() - 1) {
        string _ = s.substr(last, i - last + (i == s.size() - 1));
        ftxt += dict.count(_) ? dict[_] : _;
        if (i != s.size() - 1) ftxt += s[i];
        last = i + 1;
      }
    cout << ftxt << endl;
  }
  return 0;
}
