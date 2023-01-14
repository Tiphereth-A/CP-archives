#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int N = 1e5 + 5;
int n, a[N], b[N], f[1 << 16];
void perfect_fast_sort() {
  for (int i = 1; i <= n; ++i) ++f[a[i] & 65535];
  for (int i = 0; i < 65536; ++i) f[i] += f[i - 1];
  for (int i = n; i; --i) b[f[a[i] & 65535]--] = a[i];
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= n; ++i) ++f[b[i] >> 16 & 65535];
  for (int i = 0; i < 65536; ++i) f[i] += f[i - 1];
  for (int i = n; i; --i) a[f[b[i] >> 16 & 65535]--] = b[i];
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  perfect_fast_sort();
  for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
  return 0;
}
