#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
long long a[N];
signed main() {
  long long kase;
  cin >> kase;
  while (kase--) {
    long long n;
    cin >> n;
    long long alice = 1, bob = n;
    for (long long i = 1; i <= n; ++i) cin >> a[i];
    long long tot_a = 0, tot_b = 0, now_a = 0, now_b = 0, cnt = 0;
    bool turn = 0;
    while (alice <= bob) {
      if (turn) {
        while (now_b <= now_a && alice <= bob) now_b += a[bob--];
        tot_b += now_b;
        now_a = 0;
      } else {
        while (now_a <= now_b && alice <= bob) now_a += a[alice++];
        tot_a += now_a;
        now_b = 0;
      }
      ++cnt;
      turn ^= 1;
    }
    cout << cnt << " " << tot_a << " " << tot_b << " " << endl;
  }
  return 0;
}
