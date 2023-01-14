#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 21;
size_t n, m;
double ave;
namespace SA {
using data_type = int64_t;
using fit_type = double;
using temperature_type = double;
template <class Tp>
using seq_type = std::vector<Tp>;
using data_seq_type = seq_type<data_type>;
default_random_engine g(time(nullptr));
uniform_int_distribution<data_type> data_gen;
uniform_real_distribution<temperature_type> property(0, 1);
const temperature_type delta_T = 1 - 1e-2;
const temperature_type initial_T = 10000;
const temperature_type minimum_T = 1e-3;
fit_type fitness(const data_seq_type &seq) {
  static double dp[N][N];
  static i64 sum[N];
  memset(dp, 0x7f, sizeof(dp));
  for (size_t i = 1; i <= n; ++i) sum[i] = sum[i - 1] + seq[i - 1];
  dp[0][0] = 0;
  for (size_t i = 1; i <= n; ++i)
    for (size_t j = 1; j <= i; ++j)
      for (size_t k = 0; k < i; ++k)
        dp[i][j] =
          min(dp[i][j],
              dp[k][j - 1] + (sum[i] - sum[k] - ave) * (sum[i] - sum[k] - ave));
  return dp[n][m];
}
constexpr bool is_valid_seq(const data_seq_type &seq) { return true; }
data_seq_type new_seq_shuffle(const data_seq_type &seq) {
  data_seq_type ret(seq);
  do { random_shuffle(ret.begin(), ret.end()); } while (!is_valid_seq(ret));
  return ret;
}
data_seq_type new_seq_generate(const data_seq_type &&minimum,
                               const data_seq_type &&maximum) {
  data_seq_type ret;
  do {
    ret.clear();
    for (auto i = minimum.begin(), j = maximum.begin();
         i != minimum.end() && j != maximum.end();
         ++i, ++j)
      ret.push_back(data_gen(g) % (*j - *i) + *i);
  } while (!is_valid_seq(ret));
  return ret;
}
data_seq_type new_seq_generate_n(const data_type &&minimum,
                                 const data_type &&maximum,
                                 const size_t &&n) {
  data_seq_type ret;
  ret.resize(n);
  do {
    for (size_t i = 0; i < n; ++i)
      ret[i] = data_gen(g) % (maximum - minimum) + minimum;
  } while (!is_valid_seq(ret));
  return ret;
}
bool acceptable(const fit_type &delta_fitness, const temperature_type &now_T) {
  return delta_fitness <= 0 || exp(-delta_fitness) / now_T > property(g);
}
fit_type main_seq(data_seq_type &ans_seq) {
  fit_type ans = fitness(ans_seq), now_ans;
  for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
    size_t x, y;
    do {
      x = data_gen(g) % n;
      y = data_gen(g) % n;
    } while (x == y);
    iter_swap(ans_seq.begin() + x, ans_seq.begin() + y);
    now_ans = fitness(ans_seq);
    if (acceptable(now_ans - ans, T)) ans = now_ans;
    else iter_swap(ans_seq.begin() + x, ans_seq.begin() + y);
  }
  return ans;
}
fit_type main_range(const data_seq_type &&minimum,
                    const data_seq_type &&maximum) {
  data_seq_type ans_seq, now_seq;
  fit_type ans = numeric_limits<fit_type>::max(), now_ans;
  for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
    now_seq = new_seq_generate(move(minimum), move(maximum));
    now_ans = fitness(now_seq);
    if (acceptable(now_ans - ans, T)) {
      ans = now_ans;
      ans_seq = now_seq;
    }
  }
  return ans;
}
fit_type main_range_n(const data_type &&minimum,
                      const data_type &&maximum,
                      const size_t &&n) {
  data_seq_type ans_seq, now_seq;
  fit_type ans = numeric_limits<fit_type>::max(), now_ans;
  for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
    now_seq = new_seq_generate_n(move(minimum), move(maximum), move(n));
    now_ans = fitness(now_seq);
    if (acceptable(now_ans - ans, T)) {
      ans = now_ans;
      ans_seq = now_seq;
    }
  }
  return ans;
}
}  // namespace SA
using SA::main_range;
using SA::main_range_n;
using SA::main_seq;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
vector<i64> a;
int main() {
  auto st = clock();
  cin >> n >> m;
  a.reserve(n);
  _for(i, 1, n, _) {
    cin >> _;
    a.push_back(_);
    ave += _;
  }
  ave /= m;
  double ans = main_seq(a);
  _for(i, 1, 100) ans = min(ans, main_seq(a));
  cout << fixed << setprecision(2) << sqrt(ans / m);
  return 0;
}
