#include <bits/stdc++.h>
using namespace std;
bool vis[10];
int pp[10], ans[1000005], tot;
void add(int up) {
  int res = 0, f = 0;
  for (int i = 1; i <= up; ++i) {
    if (!pp[i]) f = 1;
    res = res * 10 + pp[i];
  }
  if (!f) ans[++tot] = res;
}
void dfs(int pos, int x, int up) {
  if (x > up) {
    add(up);
    return;
  }
  for (int i = 1, nxt; i <= 9; ++i) {
    if (!vis[i]) {
      nxt = (pos - 1 + i) % up + 1;
      if (x != up) {
        if (!pp[nxt]) {
          vis[pp[pos] = i] = 1;
          dfs(nxt, x + 1, up);
          pp[pos] = vis[i] = 0;
        }
      } else {
        if (nxt == 1) {
          vis[pp[pos] = i] = 1;
          dfs(nxt, x + 1, up);
          pp[pos] = vis[i] = 0;
        }
      }
    }
  }
}
int main() {
  int x;
  cin >> x;
  for (int i = 1; i <= 9; ++i) dfs(1, 1, i);
  sort(ans + 1, ans + 1 + tot);
  for (int i = 1; i <= tot; ++i)
    if (ans[i] > x) {
      cout << ans[i] << '\n';
      break;
    }
  return 0;
}
