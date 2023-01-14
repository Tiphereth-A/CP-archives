#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const int num_stick[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
set<i128> tmp;
int n;
i128 max_ans;
bool dfs(i128 ans = 0, int sum = 0, int dep = 0) {
  if (!tmp.count(ans)) tmp.insert(ans);
  if (sum > n) return false;
  if (sum == n) {
    max_ans = max(max_ans, ans);
    return true;
  }
  bool f = false;
  for (int i = 0; i < 10; ++i)
    if ((ans * 10 + i) % (dep + 1) == 0)
      f |= dfs(ans * 10 + i, sum + num_stick[i], dep + 1);
  return f;
}
ostream &operator<<(ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << (i128)(n / 10);
  os << (int)(n % 10);
  return os;
}
int main() {
  cin >> n;
  if (n > 139 || !dfs()) {
    cout << -1;
    return 0;
  }
  cout << max_ans;
  return 0;
}
