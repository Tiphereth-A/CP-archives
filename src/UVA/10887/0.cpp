#include <bits/stdc++.h>
using namespace std;
string s1[1500], s2[1500];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  for (int kase = 1; kase <= t; ++kase) {
    set<string> s;
    int n, m;
    cin >> n >> m;
    getline(cin, s1[0]);
    for (int i = 0; i < n; ++i) getline(cin, s1[i]);
    for (int i = 0; i < m; ++i) getline(cin, s2[i]);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) s.insert(s1[i] + s2[j]);
    cout << "Case " << kase << ": " << s.size() << endl;
  }
  return 0;
}
