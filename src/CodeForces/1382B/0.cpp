#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
int a[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    _for(i, 1, n) cin >> a[i];
    int cnt = 0;
    for (int i = 1; i <= n && a[i] == 1; ++i, ++cnt);
    cout << ((cnt == n) ^ !(cnt & 1) ? "First" : "Second") << '\n';
  __end_kase:;
  }
  return 0;
}
