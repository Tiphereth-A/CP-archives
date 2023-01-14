#include <bits/stdc++.h>
using u32 = uint32_t;
using i64 = int64_t;
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  u32 n;
  cin >> n;
  vector<i64> sa(n + 1), sb(n + 1);
  for (u32 i = 1; i <= n; ++i) cin >> sa[i];
  for (u32 i = 1; i <= n; ++i) cin >> sb[i];
  partial_sum(sa.begin(), sa.end(), sa.begin());
  partial_sum(sb.begin(), sb.end(), sb.begin());
  bool swapped = 0;
  if (sa[n] > sb[n]) {
    swapped = 1;
    swap(sa, sb);
  }
  map<i64, pair<u32, u32>> mp;
  for (u32 i = 0, j = 0; i <= n; ++i) {
    while (j <= n && sa[i] >= sb[j]) ++j;
    i64 res = sa[i] - sb[--j];
    if (mp.count(res)) {
      auto [from_a, from_b] = mp[res];
      u32 to_a = i, to_b = j;
      if (swapped) {
        swap(from_a, from_b);
        swap(to_a, to_b);
      }
      cout << to_a - from_a + 1 << '\n';
      for (u32 i = from_a; i <= to_a; ++i) cout << i << " \n"[i == to_a];
      cout << to_b - from_b + 1 << '\n';
      for (u32 i = from_b; i <= to_b; ++i) cout << i << " \n"[i == to_b];
      return 0;
    } else mp[res] = {i + 1, j + 1};
  }
  cout << "-1\n";
  return 0;
}
