#include <bits/stdc++.h>
using namespace std;
int main() {
  string s;
  cin >> s;
  regex pat(".*h.*e.*l.*l.*o.*");
  if (regex_search(s, pat)) cout << "YES" << endl;
  else cout << "NO" << endl;
  return 0;
}
