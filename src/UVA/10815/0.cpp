#include <bits/stdc++.h>
using namespace std;
int main() {
  set<string> st;
  string s;
  while (cin >> s) {
    for (int i = 0; i < s.length(); ++i)
      s[i] = isalpha(s[i]) ? tolower(s[i]) : ' ';
    stringstream ss(s);
    string _;
    while (ss >> _) st.insert(_);
  }
  for (auto i : st) cout << i << endl;
  return 0;
}
