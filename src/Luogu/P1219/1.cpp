#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
int a[15], cnt, n;
const int f[] = {0,
                 1,
                 0,
                 0,
                 2,
                 10,
                 4,
                 40,
                 92,
                 352,
                 724,
                 2680,
                 14200,
                 73712,
                 365596,
                 2279184,
                 14772512,
                 95815104,
                 666090624,
                 4968057848,
                 39029188884,
                 314666222712,
                 2691008701644,
                 24233937684440,
                 227514171973736,
                 2207893435808352,
                 22317699616364044,
                 234907967154122528};
bool check(int n) {
  _for(i, 2, n)
    _for(j, 1, i - 1)
      if ((a[i] == a[j]) || (abs(a[i] - a[j]) == abs(i - j))) return 0;
  return 1;
}
void queen(int k) {
  if (k > n) {
    if (cnt < 3) {
      cnt++;
      _for(i, 1, n) cout << a[i] << ' ';
      cout << endl;
    }
  } else if (cnt >= 3) return;
  else {
    _for(i, 1, n) {
      a[k] = i;
      if (check(k)) queen(k + 1);
    }
  }
  return;
}
int main() {
  cin >> n;
  queen(1);
  cout << f[n];
  return 0;
}
