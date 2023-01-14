#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 p, a, b, c;
i64 f(i64 x) { return (a * x % p * x % p + b * x % p + c) % p; }
i64 calc(i64 n, i64 m, i64 x) {
  unordered_map<i64, int> mp;
  i64 plen = 0, len = 0;
  for (int i = 1; i <= n + m; i++) {
    if (mp[x = f(x)]) {
      plen = mp[x] - 1;
      len = i - mp[x];
      break;
    }
    mp[x] = i;
  }
  if (!len || n <= plen || n + m <= plen + len) return 0;
  n -= plen;
  i64 nl = n / len;
  if (!nl) return m >= len ? n : n + m - len;
  else {
    if (m >= (nl + 1) * len) return n;
    else if (m >= (nl * 2 + 1) * len - n) return n + m - (nl + 1) * len;
    else if (m >= nl * len) return nl * len;
    else return m;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    i64 n, m, x;
    cin >> n >> m >> p >> x >> a >> b >> c;
    cout << calc(n, m, x) << endl;
  }
  return 0;
}
