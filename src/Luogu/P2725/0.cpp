#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
int f[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int k, n;
  cin >> k >> n;
  memset(f + 1, 0x3f, sizeof(f) - sizeof(f[0]));
  for (int i = 1, a; i <= n; ++i) {
    cin >> a;
    for (int j = a; j < N; ++j)
      if (f[j - a] + 1 <= k) f[j] = min(f[j], f[j - a] + 1);
  }
  int s = 0;
  for (int i = 1; i < N; ++i)
    if (f[i] == 0x3f3f3f3f) {
      s = i - 1;
      break;
    }
  cout << s;
  return 0;
}
