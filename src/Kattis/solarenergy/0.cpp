#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct Node {
  double t, s, a;
} star[N];
#define PI 3.14159265358979323846
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> star[i].t >> star[i].s >> star[i].a;
  vector<pair<double, double>> vec;
  double now_d = 0;
  for (int i = 1; i <= n; ++i) {
    const Node &tmp = star[i];
    if (tmp.s != 0 && tmp.t / tmp.s < PI) {
      vec.emplace_back(tmp.a - tmp.t / tmp.s, tmp.s);
      vec.emplace_back(tmp.a - tmp.t / tmp.s + 2 * PI, tmp.s);
      vec.emplace_back(tmp.a, -2 * tmp.s);
      vec.emplace_back(tmp.a + 2 * PI, -2 * tmp.s);
      vec.emplace_back(tmp.a + tmp.t / tmp.s, tmp.s);
      vec.emplace_back(tmp.a + tmp.t / tmp.s + 2 * PI, tmp.s);
    } else {
      now_d += tmp.t - tmp.s * PI;
      vec.emplace_back(tmp.a - PI, tmp.s);
      vec.emplace_back(tmp.a, -2 * tmp.s);
      vec.emplace_back(tmp.a + PI, 2 * tmp.s);
      vec.emplace_back(tmp.a + 2 * PI, -2 * tmp.s);
      vec.emplace_back(tmp.a + 3 * PI, tmp.s);
    }
  }
  sort(vec.begin(), vec.end());
  double ans = now_d, past_k = vec[0].second;
  for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
    now_d += past_k * (it->first - (it - 1)->first);
    past_k += it->second;
    ans = max(ans, now_d);
  }
  printf("%.8lf", ans);
  return 0;
}
