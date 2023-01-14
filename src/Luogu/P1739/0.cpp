#include <bits/stdc++.h>
int l, r;
using namespace std;
int main() {
  char c;
  cin >> c;
  while (c != '@') {
    if (c == '(') l++;
    else if (c == ')') r++;
    if (r > l) {
      cout << "NO";
      return 0;
    }
    cin >> c;
  }
  if (l == r) cout << "YES";
  else cout << "NO";
  return 0;
}
