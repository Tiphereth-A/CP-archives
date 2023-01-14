#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    cout << (s.length() == 1 ?
               "1 2\n" :
               (s.length() == 2 ?
                  (s[0] == s[1] ? "2 8\n" : "2 6\n") :
                  (count(s.begin(), s.end(), s.front()) == s.length() ?
                     "2 4\n" :
                     "2 2\n")));
  }
  return 0;
}
