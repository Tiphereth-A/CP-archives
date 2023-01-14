#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int a[N];
int main() {
  int n;
  cin >> n;
  int MAXN = -1, idx = 0, ans = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (MAXN < a[i]) MAXN = a[idx = i];
    ans ^= a[i];
  }
  if (!ans) {
    cout << "lose";
    return 0;
  }
  for (int i = 1; i <= n; ++i)
    if ((a[i] ^ ans) <= a[i]) {
      cout << a[i] - (a[i] ^ ans) << " " << i << endl;
      a[i] = (a[i] ^ ans);
      for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i == n];
      return 0;
    }
}
