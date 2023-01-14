#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
tree<long long,
     null_type,
     less<long long>,
     rb_tree_tag,
     tree_order_statistics_node_update>
  t;
long long read() {
  long long x = 0, f = 1;
  char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    if (ch == '-') f = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - 48;
  return x * f;
}
int main() {
  long long n, m, i, j, u[200001], v[200001];
  v[0] = 0;
  u[0] = 0;
  m = read();
  n = read();
  for (i = 1; i <= m; i++) u[i] = read();
  for (i = 1; i <= n; i++) v[i] = read();
  sort(v, v + n + 1);
  for (i = 0; i < n; i++) {
    for (j = v[i] + 1; j <= v[i + 1]; j++) t.insert((u[j] << 20) + j);
    printf("%d\n", (*t.find_by_order(u[0]) >> 20));
    u[0]++;
  }
  return 0;
}
