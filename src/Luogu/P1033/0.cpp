#include <bits/stdc++.h>
using namespace std;
int main() {
  double h, s, v, l, k, n;
  cin >> h >> s >> v >> l >> k >> n;
  int tot = 0;
  for (int i = 0; i < n; i++)
    if (i < 0.0001 + (s - sqrt((h - k) / 5) * v) + l &&
        i > (s - sqrt(h / 5) * v) - 0.0001)
      tot++;
  printf("%d", tot);
  return 0;
}
