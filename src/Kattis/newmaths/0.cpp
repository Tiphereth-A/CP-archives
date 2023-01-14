#include <bits/stdc++.h>
using namespace std;
const int table0[10] = {0, 1, -1, -1, 2, 5, 4, -1, -1, 3};
const int table1[10][10] = {{+0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                            {+0, -1, +1, -1, +2, -1, +3, -1, +4, -1},
                            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                            {+0, -1, +3, -1, +1, -1, +4, -1, +2, -1},
                            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                            {+0, -1, +2, -1, +4, -1, +1, -1, +3, -1},
                            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                            {+0, -1, +4, -1, +3, -1, +2, -1, +1, -1},
                            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
char n[35];
int a[35], ans[35] = {10};
int len, k;
bool check(int *a) {
  for (int i = 0, _; i < len; ++i) {
    _ = 0;
    for (int j = 0; j <= i; ++j) {
      if (j >= k) break;
      if (i - j >= k) continue;
      (_ += a[j] * a[i - j]) %= 10;
    }
    if (_ != n[i] - '0') return false;
  }
  return true;
}
bool dfs(int now) {
  if (now == k) {
    if (!check(a)) return false;
    if (ans[0] == 10) memcpy(ans, a, sizeof(ans));
    else {
      bool f = false;
      for (int i = k - 1; ~i; --i) {
        if (a[i] > ans[i]) break;
        if (a[i] < ans[i]) {
          f = true;
          break;
        }
      }
      if (f) memcpy(ans, a, sizeof(ans));
    }
    return true;
  }
  if (now == 0) {
    int __ = table0[n[0] - '0'];
    if (__ == -1) return false;
    bool f = 0;
    a[0] = __;
    f |= dfs(1);
    if (a[0] != 10 - __) {
      a[0] = 10 - __;
      f |= dfs(1);
    }
    return f;
  }
  int _ = 0;
  if (now & 1) {
    for (int i = 1; i <= now / 2; ++i) _ += 2 * a[i] * a[now - i] % 10;
    _ = ((n[now] - '0' - _) % 10 + 10) % 10;
  } else {
    for (int i = 1; i <= now / 2; ++i) _ += 2 * a[i] * a[now - i] % 10;
    _ = ((n[now] - '0' - _ + a[now / 2] * a[now / 2]) % 10 + 10) % 10;
  }
  if (2 * a[0] % 10 == 0 && _ == 0) {
    bool f = 0;
    for (int i = 0; i < 10; ++i) {
      a[now] = i;
      f |= dfs(now + 1);
    }
    return f;
  }
  int __ = table1[2 * a[0] % 10][_];
  if (__ == -1) return false;
  bool f = 0;
  a[now] = __;
  f |= dfs(now + 1);
  a[now] = __ + 5;
  f |= dfs(now + 1);
  return f;
}
int main() {
  cin >> n;
  len = strlen(n);
  reverse(n, n + len);
  if (n[0] == '2' || n[0] == '3' || n[0] == '7' || n[0] == '8') {
    cout << "-1";
    return 0;
  }
  k = (len + 1) / 2;
  if (dfs(0))
    for (int i = k - 1; ~i; --i) cout << ans[i];
  else cout << "-1";
  return 0;
}
