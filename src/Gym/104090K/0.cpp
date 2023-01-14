#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
const int N = 1000010;
int n, Q, cnt, ch[N][27], sz[N], num[N];
i64 sum = 0;
i64 ss[27][27];
void ins(int p, string s) {
  for (int i = 0; i < s.length(); ++i) {
    for (int j = 0; j < 26; ++j) {
      if (j != s[i] - 'a') { ss[j][s[i] - 'a'] += sz[ch[p][j]]; }
    }
    if (ch[p][s[i] - 'a']) {
      p = ch[p][s[i] - 'a'];
    } else {
      ch[p][s[i] - 'a'] = ++cnt;
      p = cnt;
    }
    sz[p]++;
  }
  num[p]++;
  sum += sz[p] - num[p];
}
void solve(int t_ = 0) {
  cin >> n >> Q;
  int root = 0;
  for (int i = 1; i <= n; ++i) {
    string S;
    cin >> S;
    ins(root, S);
  }
  for (int i = 1; i <= Q; ++i) {
    string S;
    cin >> S;
    i64 ans = sum;
    for (int j = 0; j < 26; ++j) {
      for (int k = j + 1; k < 26; ++k) { ans += ss[S[k] - 'a'][S[j] - 'a']; }
    }
    cout << ans << "\n";
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
