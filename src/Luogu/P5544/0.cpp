#include <bits/stdc++.h>
using namespace std;
const int N = 11, M = 1005;
int n, m, r;
struct Allay {
  double x, y, r;
} a[N];
struct Enemy {
  double x, y;
} b[M];
struct Result {
  double x, y;
  int score = 1;
} ans;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
namespace Simulated_annealing {
using fit_type = int;
using index_type = size_t;
using temperature_type = double;
template <class Tp>
default_random_engine g(time(nullptr));
uniform_real_distribution<double> data_gen(-RAND_MAX, RAND_MAX);
uniform_int_distribution<index_type> idx_gen;
uniform_real_distribution<temperature_type> p_gen(0, 1);
const temperature_type delta_T = 0.99;
const temperature_type initial_T = 10000;
const temperature_type minimum_T = 1e-8;
fit_type fitness(const Result &now) {
  int cnt = 0;
  double now_r = r;
  _for(i, 1, n)
    now_r = min(now_r,
                sqrt((a[i].x - now.x) * (a[i].x - now.x) +
                     (a[i].y - now.y) * (a[i].y - now.y)) -
                  a[i].r);
  if (now_r < 0) return 0;
  _for(i, 1, m)
    if (sqrt((b[i].x - now.x) * (b[i].x - now.x) +
             (b[i].y - now.y) * (b[i].y - now.y)) <= now_r)
      ++cnt;
  return cnt;
}
bool accept(const fit_type &delta_fitness, const temperature_type &now_T) {
  return delta_fitness > 0 || exp(-delta_fitness / now_T) < p_gen(g);
}
void main() {
  Result now;
  for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
    now = {ans.x + data_gen(g) * T, ans.y + data_gen(g) * T, 1};
    now.score = fitness(now);
    if (accept(now.score - ans.score, T)) {
      ans.x = now.x;
      ans.y = now.y;
      if (ans.score < now.score) ans.score = now.score;
    }
  }
}
}  // namespace Simulated_annealing
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> m >> r;
  _for(i, 1, n) cin >> a[i].x >> a[i].y >> a[i].r;
  _for(i, 1, m) cin >> b[i].x >> b[i].y;
  double sx = 0, sy = 0;
  _for(i, 1, m) {
    sx += b[i].x;
    sy += b[i].y;
  }
  ans = {sx / m, sy / m, 1};
  ans.score = Simulated_annealing::fitness(ans);
  _for(i, 1, 100) Simulated_annealing::main();
  cout << ans.score;
  return 0;
}
