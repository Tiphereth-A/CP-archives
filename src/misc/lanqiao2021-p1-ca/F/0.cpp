#include <cstring>
#include <iostream>
using namespace std;
#define _for(i, l, r) for (int i = l; i <= r; ++i)
#define _rfor(i, r, l) for (int i = r; i >= l; --i)
const int N = 105, W = 1e5 + 5;
int w[N];
bool f[W];
int main() {
  f[0] = 1;
  int n;
  cin >> n;
  int sum = 0;
  _for(i, 1, n) {
    cin >> w[i];
    sum += w[i];
  }
  int ans = 0;
  _for(i, 1, n)
    _rfor(j, sum, w[i]) f[j] |= f[j - w[i]];
  _for(i, 1, n)
    _for(j, 1, sum - w[i]) f[j] |= f[j + w[i]];
  _for(i, 1, sum) ans += f[i];
  cout << ans;
  return 0;
}
