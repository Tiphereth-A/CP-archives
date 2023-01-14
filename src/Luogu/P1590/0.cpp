#include <bits/stdc++.h>
using namespace std;
long long k, s = 1, sum = 0, ans = 0;
int t, i, j;
char a[1010];
int main() {
  cin >> t;
  while (t--) {
    ans = sum = 0;
    s = 1;
    cin >> a;
    k = strlen(a);
    for (i = 0; i < k; ++i)
      if (a[i] == '7') {
        a[i] = '6';
        for (j = i + 1; j < k; ++j) a[j] = '9';
        break;
      }
    for (i = k - 1; i >= 0; --i) {
      if (a[i] > '7') sum += s;
      s *= 9;
    }
    for (i = 0; i < k; ++i) ans = ans * 9 + a[i] - '0';
    cout << ans - sum << endl;
  }
}
