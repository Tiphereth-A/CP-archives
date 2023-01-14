#include <bits/stdc++.h>
#define N 1005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
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
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
void read(A &a, B &b, C &c, D &d) {
  read(a), read(b), read(c), read(d);
}
using namespace std;
int n, a, b, k[N], ans[N];
queue<int> q;
void bfs() {
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
}
int main() {
  read(n, a, b);
  memset(ans, -1, sizeof(ans));
  _for(i, 1, n) read(k[i]);
  q.push(a);
  ans[a] = 0;
  bfs();
  return 0;
}
