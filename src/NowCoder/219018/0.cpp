#include <bits/stdc++.h>
using namespace std;
const int D = 15, B = 1e5 + 5;
int f[B];
struct {
  int w, c;
} data[D][4];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int d, b;
    cin >> d >> b;
    memset(f, 0, sizeof(f[0]) * (b + 1));
    for (int j = 1; j <= d; ++j)
      for (int l = 0; l < 4; ++l) cin >> data[j][l].w >> data[j][l].c;
    for (int j = 1; j <= d; ++j)
      for (int k = b; ~k; --k)
        for (int l = 0; l < 4; ++l)
          if (k >= data[j][l].w)
            f[k] = max(f[k], f[k - data[j][l].w] + data[j][l].c);
    int ans = 0;
    for (int j = 0; j <= b; ++j) ans = max(ans, f[j]);
    cout << "Budget #" << i << ": Maximum of " << ans << " lives saved.";
    if (i != n) cout << endl << endl;
  }
  return 0;
}
