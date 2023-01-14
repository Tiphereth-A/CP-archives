#include <bits/stdc++.h>
using namespace std;
int x[21], n, k, sum, ans;
bool f[21];
bool isprime(int num) {
  if (num == 0 || num == 1) return false;
  int s = sqrt(num);
  for (int i = 2; i <= s; i++)
    if (num % i == 0) return false;
  return true;
}
int choose(int h, int y) {
  for (int i = y; i <= n; i++) {
    if (f[i]) {
      f[i] = false;
      sum += x[i];
      if (h == k) {
        if (isprime(sum)) ans++;
      } else choose(h + 1, i + 1);
      sum -= x[i];
      f[i] = true;
    }
  }
}
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
    f[i] = true;
  }
  choose(1, 1);
  cout << ans;
  return 0;
}
