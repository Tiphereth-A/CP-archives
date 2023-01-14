#include <bits/stdc++.h>
using namespace std;
namespace Cantor_expansion {
using std::size_t;
const size_t N = 2e5 + 5;
size_t n;
template <const std::size_t N = (std::size_t)1e6 + 5,
          typename T = std::ptrdiff_t>
class BIT {
private:
  T tree[N];
  std::size_t lowbit(std::ptrdiff_t x) { return x & (-x); }

public:
  BIT() { memset(tree, 0, sizeof(tree)); }
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(std::size_t pos, T val = 1) {
    for (std::size_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  T query(std::size_t pos) {
    T ret = 0;
    for (std::size_t i = pos; i; i = (std::ptrdiff_t)i - lowbit(i))
      ret += tree[i];
    return ret;
  }
};
BIT<N> tr;
void main(size_t p[], size_t const a[], size_t n) {
  tr.clear();
  for (size_t i = n; i; --i) {
    p[i] = tr.query(a[i]);
    tr.modify(a[i]);
  }
}
}  // namespace Cantor_expansion
namespace reverse_Cantor_expansion {
using std::size_t;
const size_t N = 2e5 + 5;
size_t n;
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
void main(size_t const p[], size_t a[], size_t n) {
  for (size_t i = 1; i <= n; ++i) tr.insert(i);
  for (size_t i = 1; i <= n; ++i) tr.remove(a[i] = tr.kth_num(p[i] + 1));
}
}  // namespace reverse_Cantor_expansion
const size_t N = 2e5 + 5;
size_t a[N], p[N], q[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", a + i);
    ++a[i];
  }
  Cantor_expansion::main(p, a, n);
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", a + i);
    ++a[i];
  }
  Cantor_expansion::main(q, a, n);
  for (size_t i = n; i; --i) p[i] += q[i];
  for (size_t i = n; i; --i) {
    p[i - 1] += p[i] / (n - i + 1);
    p[i] %= n - i + 1;
  }
  reverse_Cantor_expansion::main(p, a, n);
  for (int i = 1; i <= n; ++i) printf("%d%c", --a[i], " \n"[i == n]);
  return 0;
}
