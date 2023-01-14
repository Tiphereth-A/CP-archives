#include <bits/stdc++.h>
using namespace std;
const int d[31] = {10,    11,    100,   101,   110,   111,   1000,  1001,
                   1010,  1011,  1100,  1101,  1110,  1111,  10000, 10001,
                   10010, 10011, 10100, 10101, 10110, 10111, 11000, 11001,
                   11010, 11011, 11100, 11101, 11110, 11111, 100000};
bool dfs(int x) {
  if (x <= 1) return true;
  for (int i = 30; i >= 0; --i)
    if (x % d[i] == 0) return dfs(x / d[i]);
  return false;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    cout << (dfs(n) ? "YES" : "NO") << '\n';
  }
  return 0;
}
