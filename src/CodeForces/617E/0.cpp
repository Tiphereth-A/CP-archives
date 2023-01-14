#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 1.2e6 + OFFSET;
int blocks[N];
i64 k;
i64 xor_num[N];
struct query_node {
  int l, r, id;
  bool operator<(const query_node &other) const {
    return (blocks[l] != blocks[other.l]) ? blocks[l] < blocks[other.l] :
                                            r < other.r;
  }
} query[N];
i64 ans[N];
namespace mo {
i64 cnt[M];
i64 add(int p) {
  i64 ans = cnt[xor_num[p] ^ k];
  ++cnt[xor_num[p]];
  return ans;
}
i64 del(int p) {
  --cnt[xor_num[p]];
  return cnt[xor_num[p] ^ k];
}
}  // namespace mo
using mo::add;
using mo::del;
auto solve() -> void {
  int n, m;
  cin >> n >> m >> k;
  int sqrt_n = sqrt(n);
  _for(i, 1, n) blocks[i] = (i - 1) / sqrt_n + 1;
  _for(i, 1, n) {
    cin >> xor_num[i];
    xor_num[i] ^= xor_num[i - 1];
  }
  _for(i, 1, m, l, r) {
    cin >> l >> r;
    query[i] = {l - 1, r, i};
  }
  std::sort(query + 1, query + m + 1);
  int l = 0, r = 0;
  i64 now_ans = 0;
  mo::cnt[0] = 1;
  _for(i, 1, m) {
    int now_l = query[i].l, now_r = query[i].r;
    while (l < now_l) now_ans -= del(l++);
    while (l > now_l) now_ans += add(--l);
    while (r < now_r) now_ans += add(++r);
    while (r > now_r) now_ans -= del(r--);
    ans[query[i].id] = now_ans;
  }
  _for(i, 1, m) cout << ans[i] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
