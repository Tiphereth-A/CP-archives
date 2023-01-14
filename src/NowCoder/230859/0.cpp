#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int l[N], cnt_l;
char s[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> (s + 1);
  int n = strlen(s + 1);
  for (int i = 1, j, k; i <= n;) {
    k = (j = i) + 1;
    while (k <= n && s[j] >= s[k]) {
      j = (s[j] == s[k]) ? j + 1 : i;
      ++k;
    }
    while (i <= j) {
      l[cnt_l++] = i;
      i += k - j;
    }
  }
  l[cnt_l++] = n + 1;
  l[cnt_l++] = n + 1;
  int idx = 0;
  for (int i = 1; i <= n; ++i) {
    if (i >= l[idx + 1] && s[i] > s[i - l[idx + 1] + l[idx]]) {
      while (l[idx + 1] <= i) ++idx;
      if (s[i] <= s[i - l[idx] + l[idx - 1]]) --idx;
    }
    cout << l[idx] << ' ' << i << '\n';
  }
  return 0;
}
