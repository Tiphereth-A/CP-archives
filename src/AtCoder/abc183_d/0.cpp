#include <bits/stdc++.h>
using namespace std;
const int N = 2e5, OFFSET = 5;
i64 d[N];
int main() {
  i64 n, w;
  cin >> n >> w;
  i64 maxt = 0;
  for (i64 i = 1, s, t, p; i <= n; ++i) {
    cin >> s >> t >> p;
    d[s] += p;
    d[t] -= p;
    maxt = max(maxt, t);
  }
  for (i64 i = 0, now = 0; i < maxt; ++i)
    if ((now += d[i]) > w) {
      cout << "No";
      return 0;
    }
  cout << "Yes";
  return 0;
}
