#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define OK_          \
  {                  \
    cout << "Yes\n"; \
    continue;        \
  }
#define GG_         \
  {                 \
    cout << "No\n"; \
    continue;       \
  }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  for (; t; t--) {
    i64 a, b, c, x;
    cin >> a >> b >> c >> x;
    if (x == c || b - c == x) OK_;
    i64 _ = a - 2 * b;
    if (_ == 0) GG_;
    if ((x - c) % _ == 0) OK_;
    if ((x + c - b) % _ == 0) OK_;
    GG_;
  }
  return 0;
}
