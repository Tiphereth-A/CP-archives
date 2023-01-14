#include <cstring>
#include <iostream>
using namespace std;
int f[12881], c[3403], v[3403];
int main() {
  int n, m;
  while (cin >> n >> m) {
    for (int i = 1; i <= n; ++i) cin >> c[i] >> v[i];
    memset(f, 0, sizeof(f[0]) * (m + 1));
    for (int i = 1; i <= n; ++i)
      for (int j = m; j >= c[i]; j--)
        if (f[j] < f[j - c[i]] + v[i]) f[j] = f[j - c[i]] + v[i];
    cout << f[m] << endl;
  }
  return 0;
}
