#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using u64 = uint64_t;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  u32 n, m;
  cin >> n >> m;
  mt19937 gen{default_random_engine{}()};
  vector<u64> v(n), w;
  w.reserve(n);
  generate_n(back_inserter(w), n, [&] { return gen(); });
  for (u32 i = 0, x, y; i < m; ++i) {
    cin >> x >> y;
    --x, --y;
    v[y] += w[x];
  }
  auto g = v;
  auto sum = reduce(w.begin(), w.end(), (u64)0),
       now = reduce(v.begin(), v.end(), (u64)0);
  u32 q;
  cin >> q;
  for (u32 i = 0, t, x, y; i < q; ++i) {
    cin >> t;
    switch (t) {
      case 1:
        (cin >> x >> y), --x, --y;
        v[y] -= w[x];
        now -= w[x];
        break;
      case 2:
        (cin >> y), --y;
        now -= v[y];
        v[y] = 0;
        break;
      case 3:
        (cin >> x >> y), --x, --y;
        v[y] += w[x];
        now += w[x];
        break;
      case 4:
        (cin >> y), --y;
        now += g[y] - v[y];
        v[y] = g[y];
        break;
    }
    cout << (now == sum ? "YES" : "NO") << '\n';
  }
}
