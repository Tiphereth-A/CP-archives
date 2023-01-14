#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int least_v[] = {0,
                       1,
                       9,
                       36,
                       100,
                       225,
                       441,
                       784,
                       1296,
                       2025,
                       3025,
                       4356,
                       6084,
                       8281,
                       11025,
                       14400,
                       18496,
                       23409},
          least_s[] = {0,
                       2,
                       10,
                       28,
                       60,
                       110,
                       182,
                       280,
                       408,
                       570,
                       770,
                       1012,
                       1300,
                       1638,
                       2030,
                       2480,
                       2992,
                       3570,
                       4218};
int n, m, ans = 0x3f3f3f3f;
void dfs(int unfilled, int now_s, int now_v, int now_r, int now_h) {
  if (!unfilled) {
    if (now_v == n) ans = std::min(ans, now_s);
    return;
  }
  if (now_s + 2 * (n - now_v) / now_r > ans) return;
  if (now_v + least_v[unfilled] > n) return;
  if (now_s + least_s[unfilled] > ans) return;
  for (int next_r = now_r - 1; next_r >= unfilled; --next_r) {
    if (unfilled == m) now_s = next_r * next_r;
    for (int next_h = std::min(
           now_h - 1, (n - now_v - least_v[unfilled - 1]) / (next_r * next_r));
         next_h >= unfilled;
         --next_h) {
      dfs(unfilled - 1,
          now_s + 2 * next_h * next_r,
          now_v + next_h * next_r * next_r,
          next_r,
          next_h);
    }
  }
}
int main() {
  cin >> n >> m;
  if (n < least_v[m]) {
    cout << 0;
    return 0;
  } else if (n == least_v[m]) {
    cout << least_s[m] + 1;
    return 0;
  }
  dfs(m, 0, 0, n, sqrt(n));
  cout << (ans == 0x3f3f3f3f ? 0 : ans);
  return 0;
}
