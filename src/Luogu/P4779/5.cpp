#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define meminf(a) memset(a, 0x7f, sizeof(a))
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
const int M = 500005;
const int N = 100005;
int n, m, s, head[N], cnt, ans[N];
bool vis[N];
struct edge {
  int v, w, next;
} e[M];
struct node {
  int p, val;
  bool friend operator<(const node &a, const node &b) { return a.val > b.val; }
};
void add(int u, int v, int w) {
  e[++cnt] = {v, w, head[u]};
  head[u] = cnt;
}
void spfa() {
  std::priority_queue<node> q;
  meminf(ans);
  node now = {s, 0};
  q.push(now);
  ans[s] = 0;
  vis[s] = 1;
  while (!q.empty()) {
    node tmp = q.top();
    q.pop();
    vis[tmp.p] = 0;
    for (int i = head[tmp.p]; i; i = e[i].next) {
      int to = e[i].v, val = e[i].w;
      if (ans[to] > ans[tmp.p] + val) {
        ans[to] = ans[tmp.p] + val;
        if (!vis[to]) {
          vis[to] = 1;
          q.push(now = {to, ans[to]});
        }
      }
    }
  }
}
int main() {
  read(n, m, s);
  _for(i, 1, m) {
    int u, v, w;
    read(u, v, w);
    add(u, v, w);
  }
  spfa();
  _for(i, 1, n) printf("%d ", ans[i]);
  return 0;
}
