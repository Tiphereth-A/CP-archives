#include <algorithm>
#include <iostream>
#include <map>
#include <string>
using namespace std;
map<string, string> m;
string s, ss;
int main() {
  int n, f1 = 0;
  while (f1 != 2) {
    cin >> s;
    if (s[0] == 'X') {
      ++f1;
      continue;
    }
    if (!f1) {
      ss = s;
      sort(ss.begin(), ss.end());
      m[s] = ss;
    }
    if (f1 == 1) {
      bool f2 = 0;
      sort(s.begin(), s.end());
      for (map<string, string>::iterator it = m.begin(); it != m.end(); ++it)
        if (it->second == s) {
          f2 = 1;
          cout << it->first << endl;
        }
      if (!f2) cout << "NOT A VALID WORD" << endl;
      cout << "******" << endl;
    }
  }
  return 0;
}
