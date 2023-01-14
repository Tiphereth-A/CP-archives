#include <bits/stdc++.h>
using namespace std;
const int64_t N = 10000001;
const int64_t sqrtN = 3163;
vector<pair<int64_t, int64_t>> con[N];
int64_t mp[6001][6001];
bool flag[6001][6001];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int64_t i = 0; i <= sqrtN; ++i)
    for (int64_t j = i; j <= sqrtN; ++j)
      if (i * i + j * j < N) con[i * i + j * j].emplace_back(i, j);
  auto runif = [&](int64_t x, int64_t y, function<void(int64_t, int64_t)> f) {
    if (0 <= x && x <= 6000 && 0 <= y && y <= 6000 && flag[x][y]) f(x, y);
  };
  auto runf =
    [&](int64_t x, int64_t y, int64_t k, function<void(int64_t, int64_t)> f) {
      for (auto [x0, y0] : con[k]) {
        if (!x0 && !y0) {
          runif(x, y, f);
        } else if (!x0) {
          runif(x, y - y0, f);
          runif(x, y + y0, f);
          runif(x - y0, y, f);
          runif(x + y0, y, f);
        } else if (!y0) {
          runif(x - x0, y, f);
          runif(x + x0, y, f);
          runif(x, y - x0, f);
          runif(x, y + x0, f);
        } else {
          runif(x - x0, y - y0, f);
          runif(x - x0, y + y0, f);
          runif(x + x0, y - y0, f);
          runif(x + x0, y + y0, f);
          if (x0 == y0) continue;
          runif(x - y0, y - x0, f);
          runif(x - y0, y + x0, f);
          runif(x + y0, y - x0, f);
          runif(x + y0, y + x0, f);
        }
      }
    };
  int64_t T;
  cin >> T;
  for (int64_t _ = 1, n, m; _ <= T; ++_) {
    cout << "Case #" << _ << ":\n";
    vector<pair<int64_t, int64_t>> Point;
    cin >> n >> m;
    for (int64_t i = 1, x, y, w; i <= n; ++i) {
      cin >> x >> y >> w;
      mp[x][y] = w;
      flag[x][y] = 1;
      Point.emplace_back(x, y);
    }
    for (int64_t i = 1, op, x, y, lastans = 0; i <= m; ++i) {
      cin >> op >> x >> y;
      x = ((x + lastans) % 6000) + 1;
      y = ((y + lastans) % 6000) + 1;
      switch (op) {
        int64_t k, w;
        case 1:
          cin >> w;
          mp[x][y] = w;
          flag[x][y] = 1;
          Point.emplace_back(x, y);
          break;
        case 2: mp[x][y] = flag[x][y] = 0; break;
        case 3:
          cin >> k >> w;
          runf(x, y, k, [&](int64_t xx, int64_t yy) { mp[xx][yy] += w; });
          break;
        case 4:
          cin >> k;
          lastans = 0;
          runf(x, y, k, [&](int64_t xx, int64_t yy) { lastans += mp[xx][yy]; });
          cout << lastans << '\n';
          break;
      }
    }
    if (!Point.empty())
      for (auto &&[x, y] : Point) mp[x][y] = flag[x][y] = 0;
  }
  return 0;
}
