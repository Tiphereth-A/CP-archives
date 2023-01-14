#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  int t;
  cin >> t;
  for (int n; t; --t) {
    cin >> n;
    i64 s = i64(n) * (n + 1) / 2 * (n + 2) / 3;
    i64 circum = INT64_MAX;
    vector<tuple<int, int, int, int>> ans;
    for (i64 w = sqrt(s), h; w; --w) {
      if (s % w) continue;
      h = s / w;
      i64 now_circum = 2 * (w + h);
      if (now_circum >= circum) break;
      if (w < h) swap(w, h);
      vector<i64> v(h);
      vector<tuple<int, int, int, int>> ans2;
      for (int i = 1; i <= n; ++i) {
        int bl = n - i + 1;
        for (int j = 0; j < i; ++j) {
          bool f = 0;
          for (int k = 0; k < h; ++k)
            if (v[k] + bl <= w) {
              ans2.emplace_back(v[k], k, v[k] + bl, k + 1);
              v[k] += bl;
              f = 1;
              break;
            }
          if (!f) goto invalid__;
        }
      }
      circum = now_circum;
      ans = ans2;
    invalid__:;
    }
    cout << circum << '\n';
    for (auto &&[x, y, z, w] : ans)
      cout << x << ' ' << y << ' ' << z << ' ' << w << '\n';
  }
  return 0;
}
