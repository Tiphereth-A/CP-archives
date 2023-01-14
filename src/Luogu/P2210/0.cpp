#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 13;
bool graph[N][N];
int n;
namespace Simulated_annealing {
using data_type = int64_t;
using fit_type = int64_t;
using index_type = size_t;
using temperature_type = double;
template <class Tp>
using seq_type = std::vector<Tp>;
using data_seq_type = seq_type<data_type>;
default_random_engine g(time(nullptr));
uniform_int_distribution<data_type> data_gen;
uniform_int_distribution<index_type> idx_gen;
uniform_real_distribution<temperature_type> p_gen(0, 1);
const temperature_type delta_T = 1 - 1e-2;
const temperature_type initial_T = 10000;
const temperature_type minimum_T = 1e-3;
fit_type fitness(const data_seq_type &seq) {
  fit_type ans(0);
  _for(i, 1, n)
    _for(j, i + 1, n)
      if (graph[i][j]) ans += abs(seq[i - 1] - seq[j - 1]);
  return ans;
}
void swap_two_elements(data_seq_type &seq,
                       const index_type &x,
                       const index_type &y) {
  iter_swap(seq.begin() + x, seq.begin() + y);
}
pair<index_type, index_type> swap_two_elements_randomly(data_seq_type &seq) {
  index_type x, y;
  do {
    x = idx_gen(g) % seq.size();
    y = idx_gen(g) % seq.size();
  } while (x == y);
  swap_two_elements(seq, x, y);
  return make_pair(x, y);
}
bool accept(const fit_type &delta_fitness, const temperature_type &now_T) {
  return delta_fitness <= 0 || exp(-delta_fitness) / now_T > p_gen(g);
}
fit_type main_seq(data_seq_type &ans_seq) {
  fit_type ans = fitness(ans_seq), now_ans;
  index_type x, y;
  for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
    tie(x, y) = swap_two_elements_randomly(ans_seq);
    now_ans = fitness(ans_seq);
    if (accept(now_ans - ans, T)) ans = now_ans;
    else swap_two_elements(ans_seq, x, y);
  }
  return ans;
}
}  // namespace Simulated_annealing
int main() {
  cin >> n;
  _for(i, 1, n, x, y, z) {
    cin >> x >> y >> z;
    graph[i][x] = graph[i][y] = graph[i][z] = 1;
  }
  vector<i64> a;
  a.reserve(n);
  _for(i, 1, n) a.push_back(i);
  i64 ans = INT64_MAX;
  _for(i, 1, 2000) ans = min(ans, Simulated_annealing::main_seq(a));
  cout << ans;
  return 0;
}
