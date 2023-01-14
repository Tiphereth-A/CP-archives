#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
template <size_t N, class Tp>
class FloydSolver {
private:
  size_t n;
  Tp spath[N][N];
  static const Tp INF = std::numeric_limits<Tp>::max() / 2;

public:
  using self = FloydSolver<N, Tp>;
  FloydSolver() {}
  self &init(size_t _n = N - 1) {
    n = _n;
    for (size_t i = 0; i <= n; ++i) std::fill(spath[i], spath[i] + n + 1, INF);
    for (size_t i = 0; i <= n; ++i) spath[i][i] = 0;
    return *this;
  }
  self &addedge(size_t from, size_t to, Tp w = 1) {
    spath[from][to] = w;
    return *this;
  }
  self &floyd() {
    for (size_t k = 0; k <= n; ++k)
      for (size_t i = 0; i <= n; ++i)
        for (size_t j = 0; j <= n; ++j)
          if (spath[i][k] + spath[k][j] < spath[i][j])
            spath[i][j] = spath[i][k] + spath[k][j];
    return *this;
  }
  const Tp &query(size_t from, size_t to) const { return spath[from][to]; }
  const bool reachable(size_t from, size_t to) const {
    return query(from, to) != INF;
  }
};
FloydSolver<1005, int> fl;
int main() {
  int n, m;
  cin >> m >> n;
  string s;
  getline(cin, s);
  vector<int> p;
  fl.init(n);
  for_(i, 1, m, x) {
    p.clear();
    getline(cin, s);
    stringstream ss(s);
    while (ss >> x) p.push_back(x);
    for_(i, 0, p.size() - 1)
      for_(j, i, p.size() - 1) fl.addedge(p[i], p[j], i != j);
  }
  if (fl.floyd().reachable(1, n)) cout << fl.query(1, n) - 1;
  else cout << "NO";
}
