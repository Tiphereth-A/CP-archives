#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
template <const std::size_t N = (std::size_t)1e6 + 5>
class BT {
  std::size_t LOG_N;
  std::size_t tree[N];
  std::size_t lowbit(std::ptrdiff_t x) { return x & (-x); }
  void modify(std::size_t pos, std::size_t val = 1) {
    for (std::size_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  std::size_t sum(std::size_t pos) {
    std::size_t ret = 0;
    for (std::size_t i = pos; i; i = (std::ptrdiff_t)i - lowbit(i))
      ret += tree[i];
    return ret;
  }
  std::size_t query_rk(std::size_t pos) {
    std::size_t idx = 0;
    for (std::size_t i = LOG_N; ~i; --i) {
      idx += 1 << i;
      if (idx >= N || tree[idx] >= pos) idx -= 1 << i;
      else pos -= tree[idx];
    }
    return idx + 1;
  }

public:
  BT() {
    memset(tree, 0, sizeof(tree));
    LOG_N = ceil(log2(N));
  }
  void clear() { memset(tree, 0, sizeof(tree)); }
  void insert(std::size_t pos) { modify(pos); }
  void remove(std::size_t pos) { modify(pos, -1); }
  std::size_t get_rank(std::size_t num) { return sum(num - 1) + 1; }
  std::size_t kth_num(std::size_t k) { return query_rk(k); }
  std::size_t pre(std::size_t num) { return query_rk(sum(num - 1)); }
  std::size_t suc(std::size_t num) { return query_rk(sum(num) + 1); }
};
BT<N> tr;
size_t n, len_rk;
size_t op[N];
ptrdiff_t a[N];
ptrdiff_t rk[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (size_t i = 1; i <= n; ++i) {
    cin >> op[i] >> a[i];
    if (op[i] != 4) rk[++len_rk] = a[i];
  }
  sort(rk + 1, rk + len_rk + 1);
  len_rk = unique(rk + 1, rk + len_rk + 1) - rk - 1;
  for (size_t i = 1; i <= n; ++i)
    if (op[i] != 4) a[i] = lower_bound(rk + 1, rk + len_rk + 1, a[i]) - rk;
  for (size_t i = 1; i <= n; ++i) switch (op[i]) {
      case 1: tr.insert(a[i]); break;
      case 2: tr.remove(a[i]); break;
      case 3: cout << tr.get_rank(a[i]) << endl; break;
      case 4: cout << rk[tr.kth_num(a[i])] << endl; break;
      case 5: cout << rk[tr.pre(a[i])] << endl; break;
      case 6: cout << rk[min(tr.suc(a[i]), len_rk)] << endl; break;
    }
  return 0;
}
