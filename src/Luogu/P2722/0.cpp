#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 2e5 + 5;
long long V, n, v[N], w[N], f[N];
int main() {
  cin >> V >> n;
  for (int i = 1; i <= n; ++i) { cin >> v[i] >> w[i]; }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= V; ++j) {
      if (j >= w[i]) f[j] = std::max(f[j], f[j - w[i]] + v[i]);
    }
  cout << f[V];
  return 0;
}
