#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
int m, n, cnt[10];
int main() {
  cin >> m >> n;
  _for(i, m, n) {
    int a = i;
    while (a) {
      cnt[a % 10]++;
      a /= 10;
    }
  }
  _for(i, 0, 9) cout << cnt[i] << ' ';
  return 0;
}
