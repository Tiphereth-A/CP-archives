#include <bits/stdc++.h>
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
std::vector<u32> std_fa;
u32 find(u32 x) { return x == std_fa[x] ? x : std_fa[x] = find(std_fa[x]); }
u32 &read_input();
void print(u32 x);
template <class Tp>
using vec = std::vector<Tp>;
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define rfors_(i, r, l, s, ...) \
  for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)
#define rfor_(i, r, l, ...) rfors_(i, r, l, 1 __VA_OPT__(, ) __VA_ARGS__)
const u32 MOD = 1e9 + 7;
constexpr u64 qpow(u64 a, u64 b) {
  u64 ans = 1;
  for (; b; b /= 2, a = a * a % MOD)
    if (b & 1) ans = ans * a % MOD;
  return ans;
}
void solve() {
  u32 n = read_input(), q = read_input();
  std_fa.resize(n + 1);
  iota(std_fa.begin(), std_fa.end(), 0);
  auto get = [&]() { return find(read_input()); };
  vec<u64> fact(n + 1), ifact(n + 1);
  fact[0] = ifact[0] = 1;
  for_(i, 1, n) fact[i] = fact[i - 1] * i % MOD;
  ifact[n] = qpow(fact[n], MOD - 2);
  rfor_(i, n - 1, 1) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
  auto mCn = [&](u32 m, u32 n) {
    return m < n ? 0 : fact[m] * ifact[n] % MOD * ifact[m - n] % MOD;
  };
  vec<u32> w(n + 1, 1);
  vec<u64> a(n + 1, 1);
  while (q--) {
    u32 op = read_input();
    if (op == 1) {
      u32 x = get(), y = get();
      assert(x != y);
      w[y] += w[x];
      a[y] = a[y] * a[x] % MOD * mCn(w[y] - 1, w[x]) % MOD;
      std_fa[x] = y;
    } else {
      u32 x = get();
      print(a[x]);
    }
  }
}
std::vector<u32> input_data;
std::vector<u32> output_data;
u32 input_data_index;
u32 output_data_index;
u32 &read_input() { return input_data[input_data_index++]; }
void print(u32 x) { output_data.push_back(x); }
u32 answer_now() { return output_data[output_data_index]; }
void answer_to_next() { ++output_data_index; }
int main() {
  int seed, testcase;
  while (std::cin >> seed >> testcase) {
    {
      std_fa.clear();
      input_data.clear();
      output_data.clear();
      input_data_index = 0;
      output_data_index = 0;
      output_data.push_back(0);
    }
    std::mt19937 engine(seed);
    auto gen_next = [&](u32 from, u32 to) {
      return std::uniform_int_distribution<u32>(from, to)(engine);
    };
    u32 n, q;
    bool prop1, prop2;
    {
      assert(1 <= testcase && testcase <= 20);
      u32 N[6]{1, 10, 300, 2000, 50'000, 300'000};
      u32 Q[6]{1, 20, 600, 4000, 100'000, 300'000};
      std::set<int> prop1_set{1, 5, 8, 11, 16};
      std::set<int> prop2_set{2, 6, 9, 12, 17};
      switch (testcase) {
        case 1:
        case 2:
          n = gen_next(N[0] + 1, N[1]), q = gen_next(Q[0] + 1, Q[1]);
          break;
        case 3:
        case 4: n = N[1], q = Q[1]; break;
        case 5:
          n = gen_next(N[1] + 1, N[2]), q = gen_next(Q[1] + 1, Q[2]);
          break;
        case 6:
        case 7: n = N[2], q = Q[2]; break;
        case 8:
          n = gen_next(N[2] + 1, N[3]), q = gen_next(Q[2] + 1, Q[3]);
          break;
        case 9:
        case 10: n = N[3], q = Q[3]; break;
        case 11:
        case 12:
          n = gen_next(N[3] + 1, N[4]), q = gen_next(Q[3] + 1, Q[4]);
          break;
        case 13:
        case 14:
        case 15: n = N[4], q = Q[4]; break;
        case 16:
        case 17:
          n = gen_next(N[4] + 1, N[5]), q = gen_next(Q[4] + 1, Q[5]);
          break;
        case 18:
        case 19:
        case 20: n = N[5], q = Q[5]; break;
      }
      prop1 = prop1_set.count(testcase);
      prop2 = prop2_set.count(testcase);
    }
    {
      auto gen_node_ID = [&]() {
        u32 x = gen_next(0, n - 1);
        if (prop2) x = find(x);
        return x;
      };
      std_fa.resize(n + 1);
      iota(std_fa.begin(), std_fa.end(), 0);
      std::vector<u32> opts(q);
      u32 border = gen_next(1, std::min(n - 1, q - 1));
      std::fill(opts.begin(), opts.begin() + border, 1);
      std::fill(opts.begin() + border, opts.end(), 2);
      if (!prop1) std::shuffle(opts.begin(), opts.end(), engine);
      input_data.push_back(n);
      input_data.push_back(q);
      for (auto op : opts) {
        input_data.push_back(op);
        if (op == 2) input_data.push_back(gen_node_ID());
        else {
          u32 x, y, fx, fy;
          do {
            x = gen_node_ID();
            y = gen_node_ID();
            fx = find(x);
            fy = find(y);
          } while (fx == fy);
          input_data.push_back(x);
          input_data.push_back(y);
          std_fa[fx] = y;
        }
      }
      input_data_index = 0;
      solve();
    }
    assert(!output_data.empty());
    {
      input_data_index = 2;
      output_data_index = 0;
      auto gen_node_ID = [&]() {
        u32 &x = read_input();
        x = (x + (n - answer_now() % n)) % n;
      };
      for (u32 i = 0; i < q; ++i) {
        u32 op = read_input();
        if (op == 1) {
          gen_node_ID();
          gen_node_ID();
        } else {
          gen_node_ID();
          answer_to_next();
        }
      }
    }
    {
      std::ofstream fin(std::format("data/{}.in", testcase));
      fin << std::format("{} {}\n", n, q);
      input_data_index = 2;
      for (u32 i = 0; i < q; ++i) {
        u32 op = read_input();
        if (op == 1) {
          u32 x = read_input();
          u32 y = read_input();
          fin << std::format("{} {} {}\n", op, x, y);
        } else {
          u32 x = read_input();
          fin << std::format("{} {}\n", op, x);
        }
      }
      std::ofstream fans(std::format("data/{}.out", testcase));
      for_(i, 1, output_data.size() - 1) fans << output_data[i] << '\n';
    }
  }
  return 0;
}
