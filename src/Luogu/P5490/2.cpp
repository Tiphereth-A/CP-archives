#include <iostream>
#include <algorithm>
using ll = long long;
const int N = 1e5 + 1;
int n, a[N * 2], tot;
ll v[N * 8], w[N * 8];
struct St {
  ll x1, x2, y, o;
} b[N * 2];
int f(int y) { return std::lower_bound(a, a + tot, y) - a; }
void up(int u, int ul, int ur) {
  if (v[u]) w[u] = a[ur] - a[ul];
  else if (ul + 1 == ur) w[u] = 0;
  else w[u] = w[u * 2 + 1] + w[u * 2 + 2];
}
void add(int lf, int rg, ll o, int u = 0, int ul = 0, int ur = tot - 1) {
  if (lf == ul && rg == ur) return v[u] += o, up(u, ul, ur), void();
  int um = (ul + ur) / 2;
  if (lf < um) add(lf, std::min(rg, um), o, u * 2 + 1, ul, um);
  if (um < rg) add(std::max(lf, um), rg, o, u * 2 + 2, um, ur);
  up(u, ul, ur);
}
int main() {
  std::cin >> n;
  for (int i = 0, x1, x2, y1, y2; i < n; i++) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    b[i] = {x1, x2, y1, 1};
    b[i + n] = {x1, x2, y2, -1};
    a[i] = x1, a[i + n] = x2;
  }
  std::sort(a, a + n * 2), tot = 1;
  for (int i = 1; i < n * 2; i++)
    if (a[i] != a[tot - 1]) a[tot++] = a[i];
  std::sort(b, b + n * 2, [](St &i, St &j) -> bool { return i.y < j.y; });
  ll sum = 0;
  add(f(b[0].x1), f(b[0].x2), 1);
  for (int i = 1; i < n * 2; i++) {
    int x1 = f(b[i].x1), x2 = f(b[i].x2);
    sum += (b[i].y - b[i - 1].y) * w[0];
    add(x1, x2, b[i].o);
  }
  std::cout << sum << '\n';
}
