#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 1e5 + 5;
struct Node {
  char dir;
  int num;
  bool operator<(const Node &rhs) const { return dir < rhs.dir; }
};
array<Node, 5> a;
char s[N];
int x, y;
bool chk(int len) {
  i64 _x = 0, _y = 0;
  for (int i = 1; i <= len; ++i) {
    switch (s[i]) {
      case 'U': ++_y; break;
      case 'D': --_y; break;
      case 'L': --_x; break;
      case 'R': ++_x; break;
    }
    if (_x == x && _y == y) return 0;
  }
  return 1;
}
void solve() {
  scanf("%d%d\n", &x, &y);
  scanf("%s", s + 1);
  if (x == 0 && y == 0) {
    puts("Impossible");
    return;
  }
  a[1].num = a[2].num = a[3].num = a[4].num = 0;
  a[1].dir = 'U';
  a[2].dir = 'D';
  a[3].dir = 'L';
  a[4].dir = 'R';
  int len = strlen(s + 1);
  for (int i = 1; i <= len; ++i) switch (s[i]) {
      case 'U': ++a[1].num; break;
      case 'D': ++a[2].num; break;
      case 'L': ++a[3].num; break;
      case 'R': ++a[4].num; break;
    }
  sort(a.begin() + 1, a.end());
  do {
    int now = 0;
    for (int i = 1; i <= a[1].num; ++i) s[++now] = a[1].dir;
    for (int i = 1; i <= a[2].num; ++i) s[++now] = a[2].dir;
    for (int i = 1; i <= a[3].num; ++i) s[++now] = a[3].dir;
    for (int i = 1; i <= a[4].num; ++i) s[++now] = a[4].dir;
    if (chk(len)) {
      puts(s + 1);
      return;
    }
  } while (next_permutation(a.begin() + 1, a.end()));
  puts("Impossible");
}
int main() {
  int _t;
  scanf("%d", &_t);
  while (_t--) solve();
  return 0;
}
