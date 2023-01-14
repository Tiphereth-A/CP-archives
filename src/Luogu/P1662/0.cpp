#include <bits/stdc++.h>
using namespace std;
int num[16];
const int dir[] = {1, 1, -1, -1, 1, 1, -1, 1, -1, 1};
const int beg[] = {0, 548, 866, 892, 64, 1303, 97, 1278, 1278, 960};
int main() {
  int x;
  cin >> x;
  int blk_idx = x / 1e8, n = blk_idx * 1e8;
  int ans = beg[blk_idx], now_dir = dir[blk_idx];
  int c = 0;
  while (1) {
    ans = (ans + now_dir + 1336) % 1337 + 1;
    ++n;
    if (++num[1] == 8) --c;
    if (num[1] == 7) ++c;
    int ans = 1;
    while (num[ans] > 9) {
      num[ans] %= 10;
      ++num[++ans];
      if (num[ans] == 8) --c;
      if (num[ans] == 7) ++c;
    }
    if (n % 7 == 0 || c > 0) now_dir *= -1;
    if (n == x) break;
  }
  cout << ans;
  return 0;
}
