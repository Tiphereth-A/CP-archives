#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1005;
int n, a, b, k[N], ans[N];
std::queue<int> q;
int main() {
  scanf("%d%d%d", &n, &a, &b);
  memset(ans, 0xff, sizeof(ans));
  _for(i, 1, n) scanf("%d", k + i);
  q.push(a);
  ans[a] = 0;
  int now;
  while (!q.empty()) {
    now = q.front();
    if (now == b) break;
    q.pop();
    int next = now + k[now];
    if (next >= 1 && next <= n && (ans[next] == -1)) {
      ans[next] = ans[now] + 1;
      q.push(next);
    }
    next = now - k[now];
    if (next >= 1 && next <= n && (ans[next] == -1)) {
      ans[next] = ans[now] + 1;
      q.push(next);
    }
  }
  if (!q.empty()) printf("%d", ans[now]);
  else printf("-1");
  return 0;
}
