#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int a[N], b[N];
int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= k; ++i) cin >> a[i] >> b[i];
  sort(a + 1, a + k + 1);
  sort(b + 1, b + k + 1);
  int len_a = unique(a + 1, a + k + 1) - a - 1,
      len_b = unique(b + 1, b + k + 1) - b - 1;
  cout << 1ll * n * (len_a + len_b) - 1ll * len_a * len_b;
  return 0;
}
