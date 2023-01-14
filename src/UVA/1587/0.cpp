#include <bits/stdc++.h>
using namespace std;
struct node {
  int h, w;
  bool operator<(const node &other) const {
    return w == other.w ? h < other.h : w < other.w;
  }
} a[10];
bool judge() {
  if (a[0].h != a[1].h || a[0].w != a[1].w) return false;
  if (a[2].h != a[3].h || a[2].w != a[3].w) return false;
  if (a[4].h != a[5].h || a[4].w != a[5].w) return false;
  if (a[1].h != a[5].w) return false;
  if (a[1].w != a[2].w) return false;
  if (a[3].h != a[4].h) return false;
  return true;
}
int main() {
  while (~scanf("%d%d", &a[0].h, &a[0].w)) {
    if (a[0].h < a[0].w) swap(a[0].h, a[0].w);
    for (int i = 1; i < 6; ++i) {
      scanf("%d%d", &a[i].h, &a[i].w);
      if (a[i].h < a[i].w) swap(a[i].h, a[i].w);
    }
    sort(a, a + 6);
    puts(judge() ? "POSSIBLE" : "IMPOSSIBLE");
  }
  return 0;
}
