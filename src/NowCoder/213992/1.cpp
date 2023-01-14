#include <bits/stdc++.h>
using namespace std;
template <const std::size_t N = (std::size_t)1e2 + 5,
          class graph_t = std::ptrdiff_t>
class Floyd {
private:
  std::size_t n;
  graph_t spath[N][N];

public:
  Floyd(std::size_t _n = N - 1): n(_n) {
    memset(spath, 0x3f, sizeof(spath));
    for (std::size_t i = 1; i <= n; ++i) spath[i][i] = 0;
  }
  void resize(std::size_t _n) { n = _n; }
  void clear() { memset(spath, 0, sizeof(spath)); }
  void addedge(std::size_t from, std::size_t to, graph_t w = 1) {
    spath[from][to] = w;
  }
  void get_all_spath() {
    for (std::size_t k = 1; k <= n; ++k)
      for (std::size_t i = 1; i <= n; ++i)
        for (std::size_t j = 1; j <= n; ++j)
          if (spath[i][k] + spath[k][j] < spath[i][j])
            spath[i][j] = spath[i][k] + spath[k][j];
  }
  const graph_t &operator()(std::size_t from, std::size_t to) {
    return spath[from][to];
  }
};
Floyd<> f;
bool judge(long long k, long long l, long long b) {
  if (k > 1) return 1.0 * l <= log(b + 1 - 1.0 * b / k) / log(k);
  else if (k == 1) return l <= b;
  else return b >= 0;
}
int main() {
  int m, n;
  cin >> n >> m;
  f.resize(n);
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    f.addedge(u, v);
    f.addedge(v, u);
  }
  f.get_all_spath();
  int q;
  cin >> q;
  for (int i = 1, s, t, b; i <= q; ++i) {
    cin >> s >> t >> b;
    long long l = f(s, t);
    long long left = 0, right = b, mid, k;
    while (left <= right) {
      mid = left + ((right - left) >> 1);
      if (judge(mid, l, b)) {
        k = mid;
        left = mid + 1;
      } else right = mid - 1;
    }
    cout << k << endl;
  }
  return 0;
}
