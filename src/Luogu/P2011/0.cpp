#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) \
  for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
const int N = 200 + 5, M = 4e5 + 5;
const double EPS = 1e-8;
#define _double_equ(x, y) (abs((x) - (y)) <= EPS)
double a[N][N];
void gauss(int n) {
  _for(i, 0, n, m) {
    m = i;
    _for(j, 0, n)
      if (_double_equ(a[j][i], a[m][i])) m = j;
    if (m != i)
      _for(j, 0, n + 1) swap(a[m][j], a[i][j]);
    _for(j, i + 1, n) {
      double tmp = a[j][i] / a[i][i];
      _for(k, i, n + 1) a[j][k] -= a[i][k] * tmp;
    }
  }
  _rfor(i, n, 0) {
    _for(j, i + 1, n) a[i][n + 1] -= a[i][j] * a[j][n + 1];
    a[i][n + 1] /= a[i][i];
  }
}
double u[N];
struct Edge {
  double w, to, next;
  Edge(double _w = 0, int _to = 0, int _next = 0)
    : w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
int in[N], out[N];
void addEdge(int x, int y, double w) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
  ++in[y];
  ++out[x];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, k, q;
  cin >> n >> m >> k >> q;
  int x, y;
  double z;
  _for(i, 1, k) {
    cin >> x >> z;
    u[x] = z;
  }
  _for(i, 1, m) {
    cin >> x >> y >> z;
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  a[0][0] = 1;
  _for(i, 1, n) {
    if (_double_equ(u[i], 0)) {
      _for_graph(head, e, j, i) {
        if (to == i) continue;
        a[i][i] += 1.0 / e[j].w;
        a[i][to] -= 1.0 / e[j].w;
      }
      continue;
    }
    a[i][n + 1] = u[i];
    a[i][i] = 1;
    a[i][0] = -1;
  }
  gauss(n);
  cout << fixed << setprecision(2);
  _for(i, 1, q) {
    cin >> x >> y;
    cout << a[x][n + 1] - a[y][n + 1] << '\n';
  }
  return 0;
}
