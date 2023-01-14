#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, x;
  string str;
  cin >> n >> x >> str;
  for (auto ch : str) {
    ch == 'x' ? --x : ++x;
    x = x == -1 ? 0 : x;
  }
  cout << x;
  return 0;
}
