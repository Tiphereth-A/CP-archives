#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
char s[N];
int sum[N][26];
int dfs(int l, int r, int dep) {
  if (dep >= 26) return 0;
  if (l == r) return s[l] != dep + 'a';
  int mid = (r - l) / 2 + l;
  int l_ch = mid - l + 1 - (sum[mid][dep] - sum[l - 1][dep]),
      r_ch = r - mid - (sum[r][dep] - sum[mid][dep]);
  return min(l_ch + dfs(mid + 1, r, dep + 1), r_ch + dfs(l, mid, dep + 1));
}
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n >> (s + 1);
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < 26; ++j) sum[i][j] = sum[i - 1][j];
      ++sum[i][s[i] - 'a'];
    }
    cout << dfs(1, n, 0) << endl;
  }
  return 0;
}
