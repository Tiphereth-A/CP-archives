#include <bits/stdc++.h>
using namespace std;
int main() {
  string s;
  int k;
  cin >> s >> k;
  for (int i = 0; i < s.length(); ++i)
    if ((s[i] = tolower(s[i])) <= k + 'a' - 1) s[i] = toupper(s[i]);
  cout << s;
  return 0;
}
