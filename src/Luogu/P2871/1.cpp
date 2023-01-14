#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long v[N], w[N], f[N];
int main() {
  long long V, n;
  cin >> n >> V;
  for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i];
  for (int i = 1; i <= n; ++i)
    for (int j = V; j; --j)
      if (j >= w[i]) f[j] = max(f[j], f[j - w[i]] + v[i]);
  cout << f[V];
}
