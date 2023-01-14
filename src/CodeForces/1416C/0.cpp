#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int K = 29, N = (3e5 + OFFSET) * (K + 1);
template <int N>
struct Trie {
  struct trie_t {
    pair<int, int> next;
    vector<int> idxs;
  } data[N];
  int cnt_data = 1;
  void insert(int x, int idx, int now = 1, int dep = K) {
    if (dep < 0) return;
    int &next_p =
      ((x >> dep) & 1) ? data[now].next.second : data[now].next.first;
    if (!next_p) next_p = ++cnt_data;
    data[next_p].idxs.push_back(idx);
    insert(x, idx, next_p, dep - 1);
  }
};
Trie<N> tr;
pair<i64, i64> cnt_inversion[K + OFFSET];
void dfs(int now = 1, int dep = K) {
  int lch = tr.data[now].next.first, rch = tr.data[now].next.second;
  if (!lch && !rch) return;
  if (lch) dfs(lch, dep - 1);
  if (rch) dfs(rch, dep - 1);
  i64 now_inv = 0;
  int _ = 0;
  for (int i : tr.data[lch].idxs) {
    while (_ < tr.data[rch].idxs.size() && i > tr.data[rch].idxs[_]) ++_;
    now_inv += _;
  }
  cnt_inversion[dep].first += now_inv;
  cnt_inversion[dep].second +=
    (i64)tr.data[lch].idxs.size() * (i64)tr.data[rch].idxs.size() - now_inv;
}
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n, x) {
    cin >> x;
    tr.insert(x, i);
  }
  dfs();
  i64 ans = 0, ans_inv = 0;
  _rfor(i, K, 0) {
    ans_inv += min(cnt_inversion[i].first, cnt_inversion[i].second);
    if (cnt_inversion[i].second < cnt_inversion[i].first) ans |= (1 << i);
  }
  cout << ans_inv << " " << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
