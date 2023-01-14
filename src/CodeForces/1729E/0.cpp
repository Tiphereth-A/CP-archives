#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 query(i64 a, i64 b) {
  cout << "? " << a << ' ' << b << endl;
  i64 res;
  cin >> res;
  return res;
}
void answer(i64 res) { cout << "! " << res << endl; }
auto solve([[maybe_unused]] int t_ = 0) -> void {
  for (i64 i = 2;; ++i)
    for (i64 j = 1; j < i; ++j) {
      i64 x = query(i, j), y = query(j, i);
      if (x == -1 || y == -1) {
        answer(i - 1);
        return;
      }
      if (x != y) {
        answer(x + y);
        return;
      }
    }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
