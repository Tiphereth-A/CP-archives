#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
using u32 = std::uint32_t;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define set_nul_n_(a, n) memset(a, 0, sizeof(*(a)) * (n))
const u32 OFFSET = 5;
const u32 N = 1.5e5 + OFFSET;
const u32 M = 2.5e5 + OFFSET;
template <size_t N, typename Tp, bool _clear = false>
class BIT {
protected:
  Tp tree[N];
  ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() {
    if (_clear) this->clear();
  }
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(ptrdiff_t pos, Tp val = 1) {
    for (ptrdiff_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    for (ptrdiff_t i = pos; i; i = i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
BIT<M, int> tr;
int cnt[N];
auto solve([[maybe_unused]] int t_) -> void {
  int n, x, y;
  while (cin >> n) {
    set_nul_n_(cnt, n + 1);
    tr.clear();
    for_(i, 1, n) {
      cin >> x >> y;
      ++cnt[tr.query(x + 1)];
      tr.modify(x + 1);
    }
    for_(i, 0, n - 1) cout << cnt[i] << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
