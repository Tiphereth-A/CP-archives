#include <bits/stdc++.h>
using namespace std;
struct point {
  int x, y;
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<point> p(n);
  for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
  int ans = 0;
  for (int i = 0; i < n - 1; ++i)
    for (int j = i + 1; j < n; ++j) {
      int cnt = 2;
      point vec1{p[j].x - p[i].x, p[j].y - p[i].y};
      for (int h = 0; h < n; ++h) {
        if (h == i || h == j) continue;
        point vec2{p[h].x - p[i].x, p[h].y - p[i].y};
        cnt += (vec1.x * vec2.y == vec1.y * vec2.x);
      }
      if (cnt > ans) ans = cnt;
    }
  cout << ans;
  return 0;
}
