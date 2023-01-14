#include <bits/stdc++.h>
using namespace std;
const int M = 1005, N = 105;
struct node {
  int val, weight;
} a[N][M];
int f[M], cnt_a[M];
int main() {
  int n, m;
  cin >> m >> n;
  int max_k = 0;
  for (int i = 1, v, w, k; i <= n; ++i) {
    cin >> w >> v >> k;
    a[k][++cnt_a[k]] = {v, w};
    if (k > max_k) max_k = k;
  }
  for (int k = 1; k <= max_k; ++k)
    for (int j = m; j; --j)
      for (int i = 1; i <= cnt_a[k]; ++i)
        if (j >= a[k][i].weight)
          f[j] = max(f[j], f[j - a[k][i].weight] + a[k][i].val);
  cout << f[m];
}
