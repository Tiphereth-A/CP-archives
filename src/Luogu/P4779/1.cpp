#include <bits/stdc++.h>
template <typename T>
void read(T &t) {
  int f = 0, c = getchar();
  t = 0;
  while (!isdigit(c)) f |= c == '-', c = getchar();
  while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
  if (f) t = -t;
}
template <typename T, typename... Args>
void read(T &t, Args &...args) {
  read(t);
  read(args...);
}
#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define rrep(I, A, B) for (int I = (A); I >= (B); --I)
#define erep(I, X) for (int I = head[X]; I; I = next[I])
const int MAXN = 1e5 + 100;
const int maxm = 2e5 + 100;
int v[maxm], w[maxm], next[maxm], head[MAXN], dist[MAXN];
int minval[MAXN << 2], minpos[MAXN << 2];
int n, m, M, s, tot;
void ae(int x, int y, int z) {
  v[++tot] = y;
  w[tot] = z;
  next[tot] = head[x];
  head[x] = tot;
}
void update(int x) {
  minval[x] = std::min(minval[x << 1], minval[x << 1 | 1]);
  if (minval[x << 1] < minval[x << 1 | 1]) minpos[x] = minpos[x << 1];
  else minpos[x] = minpos[x << 1 | 1];
}
void build() {
  for (M = 1; M < n + 2; M <<= 1);
  rep(i, M, (M << 1) - 1) {
    minval[i] = i - M == s ? 0 : INT_MAX;
    minpos[i] = i - M;
  }
  rrep(i, M - 1, 1) update(i);
}
void modify(int x, int nv) {
  for (minval[x += M] = nv, x >>= 1; x; x >>= 1) update(x);
}
void dijkstra() {
  build();
  rep(i, 1, n) dist[i] = INT_MAX;
  dist[s] = 0;
  while (minval[1] < INT_MAX) {
    int x = minpos[1];
    modify(x, INT_MAX);
    erep(i, x) if (dist[v[i]] > dist[x] + w[i]) {
      dist[v[i]] = dist[x] + w[i];
      modify(v[i], dist[x] + w[i]);
    }
  }
}
int main() {
  read(n, m, s);
  rep(i, 1, m) {
    int x, y, z;
    read(x, y, z);
    ae(x, y, z);
  }
  dijkstra();
  rep(i, 1, n) printf("%d ", dist[i]);
  puts("");
  return 0;
}
