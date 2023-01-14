#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  if (s.length() == 1) cout << s << endl;
  else if (count(s.begin(), s.end() - 1, '9') == s.length() - 1)
    cout << s << endl;
  else cout << string(s.length() - 1, '9') << endl;
  return 0;
}
