#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  s[k - 1] = tolower(s[k - 1]);
  cout << s;
  return 0;
}
